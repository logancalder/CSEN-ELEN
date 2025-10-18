// ALU_tb.v
// Testbench for ALU.v
`timescale 1ns/1ps

module ALU_tb();

    reg  [31:0] A;
    reg  [31:0] B;
    reg         ADD;
    reg         NEG;
    reg         SUB;
    wire [31:0] OUT;
    wire        Z;
    wire        N;

    integer i;

    ALU uut (
        .A(A),
        .B(B),
        .ADD(ADD),
        .NEG(NEG),
        .SUB(SUB),
        .OUT(OUT),
        .Z(Z),
        .N(N)
    );

    initial begin
        $display("Starting ALU testbench...");
        $display("Time | ADD NEG SUB | A (hex)        | B (hex)        | OUT (hex)      | Z N | Comment");
        $display("-----------------------------------------------------------------------------------------");

        // Test 1: Add (A + B)
        A = 32'h00000005; B = 32'h00000003; ADD = 0; NEG = 0; SUB = 0;
        #10;
        $display("%4dns |   %b   %b   %b  | %h | %h | %h |  %b %b | Add (5+3=8)", $time, ADD, NEG, SUB, A, B, OUT, Z, N);

        // Test 2: Subtract (A - B)
        A = 32'h0000000A; B = 32'h00000004; ADD = 1; NEG = 0; SUB = 1;
        #10;
        $display("%4dns |   %b   %b   %b  | %h | %h | %h |  %b %b | Subtract (10-4=6)", $time, ADD, NEG, SUB, A, B, OUT, Z, N);

        // Test 3: Negate A (2's complement) -> -A
        A = 32'h00000007; B = 32'h00000000; ADD = 1; NEG = 1; SUB = 0;
        #10;
        $display("%4dns |   %b   %b   %b  | %h | %h | %h |  %b %b | Negate (-7 = %h)", $time, ADD, NEG, SUB, A, B, OUT, Z, N, OUT);

        // Test 4: Pass A
        A = 32'hFFFFFFFF; B = 32'h12345678; ADD = 1; NEG = 1; SUB = 1;
        #10;
        $display("%4dns |   %b   %b   %b  | %h | %h | %h |  %b %b | Pass A (A should pass)", $time, ADD, NEG, SUB, A, B, OUT, Z, N);

        // Test 5: Zero flag (make OUT==0)
        // Example: A = 0, B = 0 with add
        A = 32'h00000000; B = 32'h00000000; ADD = 0; NEG = 0; SUB = 0;
        #10;
        $display("%4dns |   %b   %b   %b  | %h | %h | %h |  %b %b | Zero flag check", $time, ADD, NEG, SUB, A, B, OUT, Z, N);

        // Test 6: Negative flag (result negative)
        // Example: 5 + (-10) -> negative
        A = 32'h00000005; B = 32'hFFFFFFF6; // -10 in 2's complement
        ADD = 0; NEG = 0; SUB = 0;
        #10;
        $display("%4dns |   %b   %b   %b  | %h | %h | %h |  %b %b | Negative flag check", $time, ADD, NEG, SUB, A, B, OUT, Z, N);

        // Additional random tests (small sweep)
        for (i = 0; i < 8; i = i + 1) begin
            A = $random;
            B = $random;
            // test add
            ADD = 0; NEG = 0; SUB = 0;
            #5;
            $display("%4dns |   %b   %b   %b  | %h | %h | %h |  %b %b | random add", $time, ADD, NEG, SUB, A, B, OUT, Z, N);
            // test subtract
            ADD = 1; NEG = 0; SUB = 1;
            #5;
            $display("%4dns |   %b   %b   %b  | %h | %h | %h |  %b %b | random sub", $time, ADD, NEG, SUB, A, B, OUT, Z, N);
        end

        $display("Finished ALU tests.");
        $finish;
    end

endmodule
