`timescale 1ns/1ps

// Decompositor 3 words to 4 output words

module decomp3to4 #(
    parameter IWIDTH = 8, // input word width
    parameter OWIDTH = 6 // decomposed word width
) (
    input wire[IWIDTH-1:0] DataIn,
    output reg[OWIDTH-1:0] DataOut,
    
    input wire ClkIn,
    input wire ClkOut,

    output wire IsFull,
    output wire IsEmpty
);

reg[IWIDTH-1:0] Buffer[2:0];
reg[2:0] InIndex = 1'b0, OutIndex = 1'b0;

assign IsFull = InIndex == 2;
assign IsEmpty = !OutIndex[1] ? 
    (OutIndex == InIndex) : 
    (OutIndex - 1 == InIndex);

always @(posedge ClkIn) begin
    if (!IsFull) begin
        Buffer[InIndex] <= DataIn;
        InIndex <= InIndex < 2 ? InIndex + 1 : 0;
    end
end

always @(posedge ClkOut) begin
    if (!IsEmpty) begin
        // TODO: decomposition not paramterized
        case (OutIndex)
            2'b00: DataOut <= Buffer[0][7:2];
            2'b01: DataOut <= { Buffer[0][1:0], Buffer[1][7:4] };
            2'b10: DataOut <= { Buffer[1][3:0], Buffer[2][7:6] };
            2'b11: DataOut <= Buffer[2][5:0];
        endcase
        OutIndex <= OutIndex < 3 ? OutIndex + 1 : 0;
    end
end

endmodule
