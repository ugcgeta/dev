module Reset_Sync (
    input  clk,
    input  ext_reset,
    output resetn
);
    reg [3:0] reset_cnt = 0;

    always_ff @(posedge clk, negedge ext_reset) begin
        if (~ext_reset) reset_cnt <= 4'b0;
        else reset_cnt <= reset_cnt + !resetn;
    end

    assign resetn = &reset_cnt;

endmodule
