
//`define __GOWIN__
`define USE_IP_MODULE

module sram_2kx8_wrapper (
    input clk,
    input reset,
    inout ce,
    input oce,
    input wre,
    input [10:0] ad,
    input [7:0] din,
    output [7:0] dout
);

`ifdef USE_IP_MODULE
    sram_2kx8_ip u_sram (
        .clk(clk),
        .reset(reset),
        .ce(ce),
        .oce(1'b1),
        .wre(wre),
        .ad(ad),
        .din(din),
        .dout(dout)
    );
`else
    sram_2kx8_behav u_sram (
        .clk(clk),
        .reset(reset),
        .ce(ce),
        .oce(1'b1),
        .wre(wre),
        .ad(ad),
        .din(din),
        .dout(dout)
    );
`endif  // USE_IP_MODULE

endmodule
