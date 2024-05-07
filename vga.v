`timescale 1ns/1ps
`include "clksrc.v"
`include "spi.v"
`include "vctl.v"
`include "vsig.v"
`include "vbuf.v"
`include "vcmdv2.v"
`include "vmmu.v"

`define ADDR_WIDTH 19      // address bit width
`define DATA_WIDTH 8       // data bit width
`define PCNT_WIDTH 10      // pixel count bit width
`define VOUT_WIDTH 6       // video out bit width

`define MAIN_CLK_PERIOD 10 // main clock period in ns

// top-level VGA module

module vga (
    input wire MainClk,
    output wire[`ADDR_WIDTH-1:0] MemAddr,
    inout wire[`DATA_WIDTH-1:0] MemData,
    output wire MemWE,
    output wire MemOE,
    output wire[`VOUT_WIDTH-1:0] ColorOut,
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
    .I(MainClk),
    .O(MainClkIBufg)
);

// pixel clock using synthesized clock@25MHz
clksrc #(
    .CLKIN_PERIOD(`MAIN_CLK_PERIOD),
    .CLK_DIV(8),
    .CLK_MUL(2)
) PixelClkSrc (
    .ClkInIBufg(MainClkIBufg),
    .ClkOutSrc(PixelClk)
);

// memory clock using synthesized clock@200MHz
clksrc #(
    .CLKIN_PERIOD(`MAIN_CLK_PERIOD),
    .CLK_DIV(2),
    .CLK_MUL(4)
) MemClkSrc (
    .ClkInIBufg(MainClkIBufg),
    .ClkOutSrc(MemClk)
);

wire[`PCNT_WIDTH-1:0] PixelCnt;
wire[`PCNT_WIDTH-1:0] LineCnt;
wire[`ADDR_WIDTH-1:0] PackReadAddr;
wire PackReadAddrReq;
wire IsActHorz;
wire IsActVert;
wire Blank;

vctl #(
    .XWIDTH(`PCNT_WIDTH),
    .YWIDTH(`PCNT_WIDTH),
    .AWIDTH(`ADDR_WIDTH),
    .XMAX(799),
    .YMAX(524),
    .HDMIN(3),
    .HDMAX(643),
    .VDMIN(799),
    .VDMAX(479)
) VideoCtl (
    .PixelClk(PixelClk),
    .PixelCnt(PixelCnt),
    .LineCnt(LineCnt),
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

wire SPIByteRecv;
wire[`DATA_WIDTH-1:0] SPIByte;

wire[`DATA_WIDTH-1:0] ReadData;
wire[`DATA_WIDTH-1:0] _ReadData;
wire ReadRdy;
wire _ReadRdy;

wire WriteClkOut;
wire[`DATA_WIDTH-1:0] WriteData;
wire[`ADDR_WIDTH-1:0] WriteAddr;

spi SPI (
    .Clk(MemClk),
    .Sclk(Sclk),
    .Mosi(Mosi),
    .CSel(CSel),
    .ByteRecv(SPIByteRecv),
    .ByteOut(SPIByte)
);

// using version 2
vcmdv2 #(
    .AWIDTH(`ADDR_WIDTH),
    .DWIDTH(`DATA_WIDTH)
) VideoCmd (
    .ByteClkIn(SPIByteRecv),
    .ByteIn(SPIByte),
    .DataModeEnable(1'b1),
    .DataClkOut(WriteClkOut),
    .AddrOut(WriteAddr)
);

assign WriteData = SPIByte;

wire[`DATA_WIDTH-1:0] PixelReadData;
wire PixelReadDataClk;

/*
wire WriteReqOverflow;
wire ReadReqOverflow;
*/
wire NoReadData;

assign PixelReadDataClk = MemClk;

vmmu #(
    .WRBUFSIZE(16),
    .WRIWIDTH(4),
    .RDBUFSIZE(3),
    .RDIWIDTH(2),
    .RDSTRIDE(1'b1),
    .AWIDTH(`ADDR_WIDTH),
    .DWIDTH(`DATA_WIDTH)
) VMMU (
    .MemClk(MemClk),

    .WriteDataIn(WriteData),
    .WriteAddrIn(WriteAddr),
    .PushWriteReq(WriteClkOut),
    
    .ReadAddrIn(PackReadAddr),
    .PushReadReq(PackReadAddrReq),
    .ReadDataOut(PixelReadData),
    .ReadDataClkOut(PixelReadDataClk),
/*
    .WriteReqQueueFull(WriteReqOverflow),
    .ReadReqQueueFull(ReadReqOverflow),
*/
    .WriteReqQueueFull(),
    .ReadReqQueueFull(),
    .ReadDataQueueEmpty(NoReadData),

    .MemAddrPort(MemAddr),
    .MemDataPort(MemData),
    .MemWriteEnable(MemWE),
    .MemOutputEnable(MemOE)
);

// FIXME: add signal to check if new data is present
vbuf #(
    .AWIDTH(`ADDR_WIDTH),
    .DWIDTH(`DATA_WIDTH)
) VideoBuf (
    .PixelClk(PixelClk), 
    .Blank(Blank),

    .ByteIn(PixelReadData),
    .ByteClkIn(PixelReadDataClk),
    .VideoOut(ColorOut)
);

endmodule
