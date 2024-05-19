

module PicoMem_BOOT_SRAM_8KB (
    input clk,
    input resetn,
    input mem_s_valid,
    input [31:0] mem_s_addr,
    input [31:0] mem_s_wdata,
    input [3:0] mem_s_wstrb,
    output mem_s_ready,
    output [31:0] mem_s_rdata
);

    reg mem_ready;

    bootram_2kx8_wrapper u_boot_sram (
        .clk(clk),
        .reset(~resetn),
        .mem_s_valid(mem_s_valid),
        .mem_s_ready(mem_ready),
        .mem_s_addr(mem_s_addr),
        .mem_s_wdata(mem_s_wdata),
        .mem_s_wstrb(mem_s_wstrb),
        .mem_s_rdata(mem_s_rdata)
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
