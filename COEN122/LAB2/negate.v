// negate.v
// 2's complement generator for 32-bit input
// out = -A = (~A) + 1
module negate (
    input  [31:0] A,
    output [31:0] out
);
    wire [31:0] inverted;
    wire       carry_out;
    wire [31:0] one = 32'b1;

    assign inverted = ~A;

    // reuse fullAdder to compute inverted + 1
    fullAdder u_add (
        .A(inverted),
        .B(one),
        .cout(carry_out),
        .sum(out)
    );

endmodule
