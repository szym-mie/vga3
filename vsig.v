`timescale 1ns/1ps

// Video Signalling Generator - generate HSync, VSync, blanks video RGB output

module vsig #(
    parameter XWIDTH = 10,
    parameter YWIDTH = 10,
	parameter HSMIN = 661,
	parameter HSMAX = 757,
	parameter VSMIN = 491,
	parameter VSMAX = 493
) (
    input wire PixelClk,
    input wire[XWIDTH-1:0] PixelCnt,
    input wire[YWIDTH-1:0] LineCnt,
    input wire IsActHorz,
	input wire IsActVert,
    output reg HSync,
    output reg VSync,
	output wire Blank
);

assign Blank = !IsActHorz || !IsActVert;

always @(posedge PixelClk) begin
    if (PixelCnt == 661) HSync <= 0;
    if (PixelCnt == 757) HSync <= 1;

    if (LineCnt == 491) VSync <= 0;
    if (LineCnt == 493) VSync <= 1;
end

endmodule
