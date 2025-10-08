// fullAdder.v
// 32-bit ripple-carry adder built out of 1-bit adders
module fullAdder (
    input  [31:0] A,
    input  [31:0] B,
    output        cout,
    output [31:0] sum
);
    wire [31:0] c; // internal carries: c[i] is carry out of bit i

    genvar i;
    generate
        for (i = 0; i < 32; i = i + 1) begin : gen_bits
            if (i == 0) begin
                oneBitAdder u_bit (
                    .a(A[i]),
                    .b(B[i]),
                    .cin(1'b0),
                    .cout(c[i]),
                    .sum(sum[i])
                );
            end else begin
                oneBitAdder u_bit (
                    .a(A[i]),
                    .b(B[i]),
                    .cin(c[i-1]),
                    .cout(c[i]),
                    .sum(sum[i])
                );
            end
        end
    endgenerate

    assign cout = c[31];

endmodule
