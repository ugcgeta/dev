

module PicoMem_SRAM_8KB (
    input clk,
    input resetn,
    input mem_s_valid,
    input [31:0] mem_s_addr,
    input [31:0] mem_s_wdata,
    input [3:0] mem_s_wstrb,
    output mem_s_ready,
    output [31:0] mem_s_rdata
);

    reg  mem_ready;
    wire mem_ce;

    assign mem_ce = mem_s_valid & ~mem_s_ready;

    sram_2kx8_wrapper u_sram_3 (
        .clk(clk),
        .reset(~resetn),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[3]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[31:24]),
        .dout(mem_s_rdata[31:24])
    );


    sram_2kx8_wrapper u_sram_2 (
        .clk(clk),
        .reset(~resetn),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[2]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[23:16]),
        .dout(mem_s_rdata[23:16])
    );

    sram_2kx8_wrapper u_sram_1 (
        .clk(clk),
        .reset(~resetn),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[1]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[15:8]),
        .dout(mem_s_rdata[15:8])
    );

    sram_2kx8_wrapper u_sram_0 (

        .clk(clk),
        .reset(~resetn),
        .ce(mem_ce),
        .oce(1'b1),
        .wre(mem_s_wstrb[0]),
        .ad(mem_s_addr[12:2]),
        .din(mem_s_wdata[7:0]),
        .dout(mem_s_rdata[7:0])
    );

    always @(posedge clk) begin
        if (~resetn) begin
            mem_ready <= 1'b0;
        end else begin
            if (mem_ready) begin
                mem_ready <= 1'b0;
            end else if (mem_s_valid) begin
                mem_ready <= 1'b1;
            end
        end
    end

    assign mem_s_ready = mem_ready;

endmodule
