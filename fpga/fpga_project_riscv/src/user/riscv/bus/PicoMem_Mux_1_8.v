`timescale 1ns / 1ps

module PicoMem_Mux_1_8 #(
    parameter reg [31:0] PICOS0_ADDR_BASE = 32'h8000_0000,
    parameter reg [31:0] PICOS0_ADDR_MASK = 32'h0F00_0000,
    parameter reg [31:0] PICOS1_ADDR_BASE = 32'h8100_0000,
    parameter reg [31:0] PICOS1_ADDR_MASK = 32'h0F00_0000,
    parameter reg [31:0] PICOS2_ADDR_BASE = 32'h8200_0000,
    parameter reg [31:0] PICOS2_ADDR_MASK = 32'h0F00_0000,
    parameter reg [31:0] PICOS3_ADDR_BASE = 32'h8300_0000,
    parameter reg [31:0] PICOS3_ADDR_MASK = 32'h0F00_0000,
    parameter reg [31:0] PICOS4_ADDR_BASE = 32'h8400_0000,
    parameter reg [31:0] PICOS4_ADDR_MASK = 32'h0F00_0000,
    parameter reg [31:0] PICOS5_ADDR_BASE = 32'h8500_0000,
    parameter reg [31:0] PICOS5_ADDR_MASK = 32'h0F00_0000,
    parameter reg [31:0] PICOS6_ADDR_BASE = 32'h8600_0000,
    parameter reg [31:0] PICOS6_ADDR_MASK = 32'h0F00_0000,
    parameter reg [31:0] PICOS7_ADDR_BASE = 32'h8700_0000,
    parameter reg [31:0] PICOS7_ADDR_MASK = 32'h0F00_0000
) (
    input picos0_ready,
    input [31:0] picos0_rdata,
    input picos1_ready,
    input [31:0] picos1_rdata,
    input picom_valid,
    input [31:0] picom_addr,
    input [31:0] picom_wdata,
    input [3:0] picom_wstrb,
    input picos2_ready,
    input [31:0] picos2_rdata,
    input picos3_ready,
    input [31:0] picos3_rdata,
    input picos4_ready,
    input [31:0] picos4_rdata,
    input picos5_ready,
    input [31:0] picos5_rdata,
    input picos6_ready,
    input [31:0] picos6_rdata,
    input picos7_ready,
    input [31:0] picos7_rdata,

    output picos0_valid,
    output [31:0] picos0_addr,
    output [31:0] picos0_wdata,
    output [3:0] picos0_wstrb,
    output picos1_valid,
    output [31:0] picos1_addr,
    output [31:0] picos1_wdata,
    output [3:0] picos1_wstrb,
    output picom_ready,
    output [31:0] picom_rdata,
    output picos2_valid,
    output [31:0] picos2_addr,
    output [31:0] picos2_wdata,
    output [3:0] picos2_wstrb,
    output picos3_valid,
    output [31:0] picos3_addr,
    output [31:0] picos3_wdata,
    output [3:0] picos3_wstrb,
    output picos4_valid,
    output [31:0] picos4_addr,
    output [31:0] picos4_wdata,
    output [3:0] picos4_wstrb,
    output picos5_valid,
    output [31:0] picos5_addr,
    output [31:0] picos5_wdata,
    output [3:0] picos5_wstrb,
    output picos6_valid,
    output [31:0] picos6_addr,
    output [31:0] picos6_wdata,
    output [3:0] picos6_wstrb,
    output picos7_valid,
    output [31:0] picos7_addr,
    output [31:0] picos7_wdata,
    output [3:0] picos7_wstrb
);
    wire picos0_match = ~|((picom_addr ^ PICOS0_ADDR_BASE) & PICOS0_ADDR_MASK);
    wire picos1_match = ~|((picom_addr ^ PICOS1_ADDR_BASE) & PICOS1_ADDR_MASK);
    wire picos2_match = ~|((picom_addr ^ PICOS2_ADDR_BASE) & PICOS2_ADDR_MASK);
    wire picos3_match = ~|((picom_addr ^ PICOS3_ADDR_BASE) & PICOS3_ADDR_MASK);
    wire picos4_match = ~|((picom_addr ^ PICOS4_ADDR_BASE) & PICOS4_ADDR_MASK);
    wire picos5_match = ~|((picom_addr ^ PICOS5_ADDR_BASE) & PICOS5_ADDR_MASK);
    wire picos6_match = ~|((picom_addr ^ PICOS6_ADDR_BASE) & PICOS6_ADDR_MASK);
    wire picos7_match = ~|((picom_addr ^ PICOS7_ADDR_BASE) & PICOS7_ADDR_MASK);

    wire picos0_sel = picos0_match;
    wire picos1_sel = picos1_match & (~picos0_match);
    wire picos2_sel = picos2_match & (~picos0_match) & (~picos1_match);
    wire picos3_sel = picos3_match & (~picos0_match) & (~picos1_match) & (~picos2_match);
    wire picos4_sel = picos4_match & (~picos0_match) & (~picos1_match) & (~picos2_match)
                     & (~picos3_match);
    wire picos5_sel = picos5_match & (~picos0_match) & (~picos1_match) & (~picos2_match)
                     & (~picos3_match) & (~picos4_match);
    wire picos6_sel = picos5_match & (~picos0_match) & (~picos1_match) & (~picos2_match)
                     & (~picos3_match) & (~picos4_match) & (~picos5_match);
    wire picos7_sel = picos7_match & (~picos0_match) & (~picos1_match) & (~picos2_match)
                     & (~picos3_match) & (~picos4_match) & (~picos5_match) & (~picos6_match);

    // master
    assign picom_rdata = picos0_sel ? picos0_rdata :
                      picos1_sel ? picos1_rdata :
                      picos2_sel ? picos2_rdata :
                      picos3_sel ? picos3_rdata :
                      picos4_sel ? picos4_rdata :
                      picos5_sel ? picos5_rdata :
                      picos6_sel ? picos6_rdata :
                      picos7_sel ? picos7_rdata :
                      32'b0;

    assign picom_ready = picos0_sel ? picos0_ready :
                      picos1_sel ? picos1_ready :
                      picos2_sel ? picos2_ready :
                      picos3_sel ? picos3_ready :
                      picos4_sel ? picos4_ready :
                      picos5_sel ? picos5_ready :
                      picos6_sel ? picos6_ready :
                      picos7_sel ? picos7_ready :
                      1'b0;

    // slave 0
    assign picos0_valid = picom_valid & picos0_sel;
    assign picos0_addr = picom_addr;
    assign picos0_wdata = picom_wdata;
    assign picos0_wstrb = picom_wstrb;

    // slave 1
    assign picos1_valid = picom_valid & picos1_sel;
    assign picos1_addr = picom_addr;
    assign picos1_wdata = picom_wdata;
    assign picos1_wstrb = picom_wstrb;

    // slave 2
    assign picos2_valid = picom_valid & picos2_sel;
    assign picos2_addr = picom_addr;
    assign picos2_wdata = picom_wdata;
    assign picos2_wstrb = picom_wstrb;

    // slave 3
    assign picos3_valid = picom_valid & picos3_sel;
    assign picos3_addr = picom_addr;
    assign picos3_wdata = picom_wdata;
    assign picos3_wstrb = picom_wstrb;

    // slave 4
    assign picos4_valid = picom_valid & picos4_sel;
    assign picos4_addr = picom_addr;
    assign picos4_wdata = picom_wdata;
    assign picos4_wstrb = picom_wstrb;

    // slave 5
    assign picos5_valid = picom_valid & picos5_sel;
    assign picos5_addr = picom_addr;
    assign picos5_wdata = picom_wdata;
    assign picos5_wstrb = picom_wstrb;

    // slave 6
    assign picos6_valid = picom_valid & picos6_sel;
    assign picos6_addr = picom_addr;
    assign picos6_wdata = picom_wdata;
    assign picos6_wstrb = picom_wstrb;

    // slave 7
    assign picos7_valid = picom_valid & picos7_sel;
    assign picos7_addr = picom_addr;
    assign picos7_wdata = picom_wdata;
    assign picos7_wstrb = picom_wstrb;
endmodule
