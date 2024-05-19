// 汎用sram定義、IPを使用するときは不要
module sram_2kx8_behav (
    input clk,
    input reset,
    inout ce,
    input oce,
    input wre,
    input [10:0] ad,
    input [7:0] din,
    output [7:0] dout
);
    //reg [7:0] mem [2047:0];
    reg [7:0] mem[2048];
    reg [7:0] mem_out;

    always @(posedge clk) begin
        if (ce) begin
            if (wre) begin
                mem[ad] <= din;
            end
            mem_out <= mem[ad];
        end
    end

    assign dout = mem_out;

endmodule
