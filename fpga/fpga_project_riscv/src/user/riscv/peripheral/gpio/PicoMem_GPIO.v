module PicoMem_GPIO (
    input clk,
    input resetn,
    input busin_valid,
    input [31:0] busin_addr,
    input [31:0] busin_wdata,
    input [3:0] busin_wstrb,
    output busin_ready,
    output [31:0] busin_rdata,
    inout [31:0] io
);
    reg [31:0] out_r;
    reg [31:0] oe_r;
    reg [31:0] rdata_r;
    reg ready_r;

    always @(posedge clk) begin
        if (!resetn) begin
            ready_r <= 1'b0;
            out_r <= 32'b0;
            oe_r <= 32'b0;
        end else begin
            ready_r <= 1'b0;
            if (busin_valid && !ready_r) begin
                ready_r <= 1'b1;
                case (busin_addr[3:2])
                    2'b00: begin
                        if (busin_wstrb[3]) out_r[31:24] <= busin_wdata[31:24];
                        if (busin_wstrb[2]) out_r[24:16] <= busin_wdata[24:16];
                        if (busin_wstrb[1]) out_r[15:8] <= busin_wdata[15:8];
                        if (busin_wstrb[0]) out_r[7:0] <= busin_wdata[7:0];
                        // Read and write won't happen at same transaction so no issue on late updating
                        rdata_r <= out_r;
                    end
                    2'b01: begin
                        rdata_r <= io;
                    end
                    2'b10: begin
                        if (busin_wstrb[3]) oe_r[31:24] <= busin_wdata[31:24];
                        if (busin_wstrb[2]) oe_r[24:16] <= busin_wdata[24:16];
                        if (busin_wstrb[1]) oe_r[15:8] <= busin_wdata[15:8];
                        if (busin_wstrb[0]) oe_r[7:0] <= busin_wdata[7:0];
                        // Read and write won't happen at same transaction so no issue on late updating
                        rdata_r <= oe_r;
                    end
                    default: rdata_r <= 32'hDEADBEEF;
                endcase
            end
        end
    end

    assign busin_ready = ready_r;
    assign busin_rdata = rdata_r;

    genvar i;
    generate
        for (i = 0; i < 32; i = i + 1) begin : gen_gpio
            assign io[i] = oe_r[i] ? out_r[i] : 1'bz;
        end
    endgenerate

endmodule
