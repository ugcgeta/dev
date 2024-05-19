//`define __GOWIN__
`define USE_IP_MODULE
//`include "PicoMem_2kx8_SRAM_behav.v"

module bootram_2kx8_wrapper (
    input clk,
    input reset,
    input mem_s_valid,
    input mem_s_ready,
    input [31:0] mem_s_addr,
    input [31:0] mem_s_wdata,
    input [3:0] mem_s_wstrb,
    output [31:0] mem_s_rdata
);

    wire mem_ce;

    assign mem_ce = mem_s_valid & ~mem_s_ready;

`ifdef USE_IP_MODULE
    bootram_2kx8_ip_3 u_sram_3 (
        .clk(clk),
        .reset(reset),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[3]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[31:24]),
        .dout(mem_s_rdata[31:24])
    );
`else
    PicoMem_2kx8_SRAM_behav u_sram_3 (
        .clk(clk),
        .reset(reset),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[3]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[31:24]),
        .dout(mem_s_rdata[31:24])
    );
`endif

`ifdef USE_IP_MODULE
    bootram_2kx8_ip_2 u_sram_2 (
        .clk(clk),
        .reset(reset),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[2]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[23:16]),
        .dout(mem_s_rdata[23:16])
    );
`else
    PicoMem_2kx8_SRAM_behav u_sram_2 (
        .clk(clk),
        .reset(reset),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[2]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[23:16]),
        .dout(mem_s_rdata[23:16])
    );
`endif

`ifdef USE_IP_MODULE
    bootram_2kx8_ip_1 u_sram_1 (
        .clk(clk),
        .reset(reset),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[1]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[15:8]),
        .dout(mem_s_rdata[15:8])
    );
`else
    PicoMem_2kx8_SRAM_behav u_sram_1 (
        .clk(clk),
        .reset(reset),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[1]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[15:8]),
        .dout(mem_s_rdata[15:8])
    );
`endif

`ifdef USE_IP_MODULE
    bootram_2kx8_ip_0 u_sram_0 (
        .clk(clk),
        .reset(reset),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[0]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[7:0]),
        .dout(mem_s_rdata[7:0])
    );
`else
    PicoMem_2kx8_SRAM_behav u_sram_0 (
        .clk(clk),
        .reset(reset),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[0]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[7:0]),
        .dout(mem_s_rdata[7:0])
    );
`endif


endmodule
