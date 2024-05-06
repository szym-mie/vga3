`timescale 1ns/1ps

// Sequence generator - First In First Out

module seqfifo #( 
    parameter BUFSIZE = 16, // buffer size
    parameter STRIDE = 1, // stride of range elements
    parameter IWIDTH = 4, // buffer index width
    parameter WWIDTH = 8 // memory word width
) (
    input wire[WWIDTH-1:0] DataIn,
    output reg[WWIDTH-1:0] DataOut,
    
    input wire ClkIn,
    input wire ClkOut,

    output wire IsFull,
    output wire IsEmpty
);

reg[WWIDTH-1:0] DataStart;
reg[IWIDTH-1:0] OutIndex = 1'b0;

assign IsFull = OutIndex == 1'b0;
assign IsEmpty = OutIndex == BUFSIZE - 1;

always @(posedge ClkIn) begin
    DataStart <= DataIn;
    OutIndex = 1'b0;
end

always @(posedge ClkOut) begin
    if (!IsEmpty) begin
        DataOut <= OutIndex ? DataOut + STRIDE : DataStart;
        OutIndex <= OutIndex + 1'b1;
    end
end

endmodule
