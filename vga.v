`timescale 1ns/1ps
`include "clksrc.v"
`include "spi.v"
`include "vctl.v"
`include "vsig.v"
`include "vbuf.v"
`include "vcmdv2.v"
`include "vmmu.v"

`define ADDR_WIDTH 19
`define DATA_WDITH 8
`define PCNT_WIDTH 10
`define VOUT_WIDTH 6

`define MAIN_CLK_PERIOD 10

// Top-level VGA module

module vga (
    input wire MainClkSrc,
    output wire[ADDR_WIDTH-1:0] MemAddr,
    inout wire[DATA_WDITH-1:0] MemData,
    output wire MemWE,
    output wire MemOE,
    output wire[VOUT_WIDTH-1:0] ColorOut,
    output wire HSyncOut,
    output wire VSyncOut,
    input wire Sclk,
    input wire Mosi,
    input wire CSel
);

wire MainClkIBufg;
wire PixelClk;
wire MemClk;

IBUFG MainClkIbufgInst(
    .I(MainClkSrc),
    .O(MainClkIBufg)
);

// pixel clock using synthesized clock@25MHz
clksrc #(
    .CLKIN_PERIOD(`MAIN_CLK_PERIOD),
    .CLK_DIV(8),
    .CLK_MUL(2)
) PixelClkSrc (
    .ClkInIBufg(MainClkIBufg),
    .ClkOutSrc(PixelClkSrc)
);

// memory clock using synthesized clock@200MHz
clksrc #(
    .CLKIN_PERIOD(`MAIN_CLK_PERIOD),
    .CLK_DIV(2),
    .CLK_MUL(4)
) MemClkSrc (
    .ClkInIBufg(MainClkIBufg),
    .ClkOutSrc(MemClkSrc)
);

wire[PCNT_WIDTH-1:0] PixelCnt;
wire[PCNT_WIDTH-1:0] LineCnt;
wire[ADDR_WIDTH-1:0] PackReadAddr;
wire PackReadAddrReq;
wire IsActHorz;
wire IsActVert;
wire Blank;

vctl #(
    .XWIDTH(`PCNT_WIDTH),
    .YWIDTH(`PCNT_WIDTH),
    .XMAX(799),
    .YMAX(524),
    .HDMIN(3),
    .HDMAX(643),
    .VDMIN(799),
	.VDMAX(479)
) VideoCtl (
    .PixelClk(PixelClk),
    .PixelCounter(PixelCnt),
    .LineCounter(LineCnt),
    .AddrOut(PackReadAddr),
    .AddrClkOut(PackReadAddrReq),
    .IsActHorz(IsActHorz),
	.IsActVert(IsActVert)
);


vsig #(
    .XWIDTH(`PCNT_WIDTH),
    .YWIDTH(`PCNT_WIDTH),
	.HSMIN(661),
	.HSMAX(757),
	.VSMIN(491),
	.VSMAX(493)
) VideoSig (
    .PixelClk(PixelClk),
    .PixelCnt(PixelCnt),
    .LineCnt(LineCnt),
    .IsActHorz(IsActHorz),
    .IsActVert(IsActVert),
    .HSync(HSyncOut),
    .VSync(VSyncOut),
    .Blank(Blank)
);

wire SpiByteRecv;
wire[DATA_WDITH-1:0] SpiByte;

wire[DATA_WDITH-1:0] ReadData;
wire[DATA_WDITH-1:0] _ReadData;
wire ReadRdy;
wire _ReadRdy;

wire WriteClkOut;
wire[DATA_WDITH-1:0] WriteData;
wire[ADDR_WIDTH-1:0] WriteAddr;

spi Spi (
    .Clk(MemClk),
    .Sclk(Sclk),
	.Mosi(Mosi),
	.CSel(CSel),
	.ByteRecv(SpiByteRecv),
	.ByteOut(SpiByte)
);

// using version 2
vcmdv2 #(
    .AWIDTH(`ADDR_WIDTH),
    .DWIDTH(`DATA_WDITH)
) VideoCmd (
	.ByteClkIn(SpiByteRecv),
    .ByteIn(SpiByte),
	.DataModeEnable(1'b1),
    .DataClkOut(WriteClkOut),
	.AddrOut(WriteAddr)
);

assign WriteData = SpiByte;

wire PixelReadData;
wire PixelReadDataClk;

wire WriteReqOverflow;
wire ReadReqOverflow;
wire NoReadData;

assign PixelReadDataClk = !NoReadData ? MemClk : 1'b0;

vmmu #(
    .WRBUFSIZE(16),
    .RDBUFSIZE(3),
    .IWIDTH(4),
    .AWIDTH(`ADDR_WIDTH),
    .DWIDTH(`DATA_WDITH)
) VMMU (
    .MemClk(MemClk),

    .WriteDataIn(WriteData),
    .WriteAddrIn(WriteAddr),
    .PushWriteReq(WriteClkOut),
    
    .ReadAddrIn(PackReadAddr),
    .PushReadReq(PackReadAddrReq),
    .ReadDataOut(PixelReadData),
    .ReadDataClkOut(PixelReadDataClk),

    .WriteReqQueueFull(WriteReqOverflow),
    .ReadReqQueueFull(ReadReqOverflow),
    .ReadDataQueueEmpty(NoReadData),

    .MemAddrPort(MemAddr),
    .MemDataPort(MemData),
    .MemWriteEnable(MemWE),
    .MemOutputEnable(MemOE)
);

vbuf #(
    .AWIDTH(`ADDR_WIDTH),
    .DWIDTH(`DATA_WDITH)
) VideoBuf (
    .PixelClk(PixelClk), 
    .Blank(Blank),

    .ByteIn(PixelReadData),
    .ByteClkIn(PixelReadDataClk),
    .VideoOut(ColorOut)
);

// TODO: remove
/*
always @(posedge ReadRdy) begin
	 if (WriteBufferIndex < 2)
	     WriteBufferIndex <= WriteBufferIndex + 1'b1;
	 else
	     WriteBufferIndex <= 1'b0;
		  
	 // if (PixelCounter <= 640) ReadAddr <= ReadAddr + 1'b1;
    if (LineCounter >= 480) ReadAddr <= 1'b0;
	 else ReadAddr <= ReadAddr + 1'b1;
end
*/

endmodule
