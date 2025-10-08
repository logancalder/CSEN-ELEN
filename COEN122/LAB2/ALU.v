// ALU.v
// Top-level ALU (hardcoded 32 bits)
// Ports:
//   A[31:0], B[31:0] : data inputs
//   ADD, NEG, SUB    : control inputs (as specified in the lab truth table)
//   OUT[31:0]        : result
//   Z                : zero flag (1 if OUT == 0)
//   N                : negative flag (1 if OUT[31] == 1)
module ALU (
    input  [31:0] A,
    input  [31:0] B,
    input         ADD,
    input         NEG,
    input         SUB,
    output [31:0] OUT,
    output        Z,
    output        N
);

    // Generate -A and -B
    wire [31:0] negA, negB;
    negate u_negA (.A(A), .out(negA));
    negate u_negB (.A(B), .out(negB));

    // Decide signal1 (either A or -A)
    // From truth table:
    // Use -A when (ADD == 1 && NEG == 1 && SUB == 0) (the 2's-complement operation).
    wire sel1;
    assign sel1 = ADD & NEG & (~SUB);
    wire [31:0] sig1;
    twoToOne u_t21 (.A(A), .negA(negA), .sel(sel1), .out(sig1));

    // Decide signal2 (B, 0, or -B)
    // Encoding for threeToOne:
    //   00 -> B
    //   01 -> 0
    //   10 -> -B
    reg [1:0] sel2;
    always @(*) begin
        // Default to zero
        sel2 = 2'b01;
        // Add case: ADD=0, NEG=0, SUB=0 -> B
        if ((ADD == 1'b0) && (NEG == 1'b0) && (SUB == 1'b0)) sel2 = 2'b00;
        // Subtract: ADD=1, NEG=0, SUB=1 -> -B
        else if ((ADD == 1'b1) && (NEG == 1'b0) && (SUB == 1'b1)) sel2 = 2'b10;
        // 2's complement (ADD=1,NEG=1,SUB=0) -> zero
        // Pass A (ADD=1,NEG=1,SUB=1) -> zero
        else sel2 = 2'b01;
    end

    wire [31:0] sig2;
    threeToOne u_t31 (.B(B), .negB(negB), .sel(sel2), .out(sig2));

    // Final adder: sig1 + sig2
    wire carry_out;
    fullAdder u_main_add (.A(sig1), .B(sig2), .cout(carry_out), .sum(OUT));

    // Flags
    assign Z = ~(|OUT);      // Z = 1 iff OUT == 0 (reduction OR); invert it
    assign N = OUT[31];      // N = 1 iff OUT is negative (MSB set)

endmodule
