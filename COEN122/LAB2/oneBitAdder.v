// oneBitAdder.v
// 1-bit full adder primitive (sum + carry out)
module oneBitAdder (
    input  a,
    input  b,
    input  cin,
    output cout,
    output sum
);

    assign sum  = a ^ b ^ cin;
    assign cout = (a & b) | (b & cin) | (a & cin);

endmodule
