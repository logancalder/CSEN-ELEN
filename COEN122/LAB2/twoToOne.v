// twoToOne.v
// 2-to-1 multiplexer (select between A and negA)
// sel = 0 -> A, sel = 1 -> negA
module twoToOne (
    input  [31:0] A,
    input  [31:0] negA,
    input         sel,
    output [31:0] out
);
    // bitwise selection
    assign out = (sel ? negA : A);
endmodule
