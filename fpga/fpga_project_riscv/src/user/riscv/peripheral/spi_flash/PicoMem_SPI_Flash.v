module PicoMem_SPI_Flash (
    input clk,
    input resetn,
    input flash_mem_valid,
    input [31:0] flash_mem_addr,
    input [31:0] flash_mem_wdata,
    input [3:0] flash_mem_wstrb,
    input flash_cfg_valid,
    input [31:0] flash_cfg_addr,
    input [31:0] flash_cfg_wdata,
    input [3:0] flash_cfg_wstrb,
    output flash_mem_ready,
    output [31:0] flash_mem_rdata,
    output flash_cfg_ready,
    output [31:0] flash_cfg_rdata,
    output flash_clk,
    output flash_csb,
    inout flash_mosi,
    inout flash_miso
);

    wire flash_io0_oe;
    wire flash_io0_di;
    wire flash_io0_do;
    wire flash_io1_oe;
    wire flash_io1_di;
    wire flash_io1_do;

    spimemio_puya u_spimemio (
        .clk(clk),
        .resetn(resetn),

        .valid(flash_mem_valid),
        .ready(flash_mem_ready),
        .addr (flash_mem_addr[23:0]),
        .rdata(flash_mem_rdata),

        .cfgreg_we({4{flash_cfg_valid}} & flash_cfg_wstrb),
        .cfgreg_di(flash_cfg_wdata),
        .cfgreg_do(flash_cfg_rdata),

        .flash_clk(flash_clk),
        .flash_csb(flash_csb),

        .flash_io0_oe(flash_io0_oe),
        .flash_io0_di(flash_io0_di),
        .flash_io0_do(flash_io0_do),

        .flash_io1_oe(flash_io1_oe),
        .flash_io1_di(flash_io1_di),
        .flash_io1_do(flash_io1_do)
    );
    assign flash_cfg_ready = flash_cfg_valid;

    assign flash_mosi = flash_io0_oe ? flash_io0_do : 1'bz;
    assign flash_io0_di = flash_mosi;
    assign flash_miso = flash_io1_oe ? flash_io1_do : 1'bz;
    assign flash_io1_di = flash_miso;

endmodule
