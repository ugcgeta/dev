module top (
    input sys_clk,   // clk input
    input sys_rst_n, // reset input
    //input        sw2

    // hdmi
    /*
    output tmds_clk_p,
    output tmds_clk_n,
    output [2:0] tmds_data_p,
    output [2:0] tmds_data_n
*/
    output flash_clk,
    output flash_csb,
    inout  flash_mosi,
    inout  flash_miso,

    input ser_rx,
    output ser_tx,
    inout [6:0] gpio,
    input ser_rx_ip,
    output ser_tx_ip,
    inout scl,
    inout sda
);

    logic resetn;

    Reset_Sync u_Reset_Sync (
        .clk(sys_clk),
        .ext_reset(sys_rst_n),
        .resetn(resetn)
    );

    riscv_top u_riscv_top (
        .core_clk(sys_clk),
        .resetn  (resetn),

        .flash_clk (flash_clk),
        .flash_csb (flash_csb),
        .flash_mosi(flash_mosi),
        .flash_miso(flash_miso),

        .ser_rx(ser_rx),
        .ser_tx(ser_tx),
        .gpio  (gpio),
        .ser_rx_ip(ser_rx_ip),
        .ser_tx_ip(ser_tx_ip),
        .scl(scl),
        .sda(sda)
    );

/*
    logic [23:0] counter;
    logic [ 5:0] led_tmp;
    logic [23:0] count_max;

    assign count_max = sw2 ? 24'd1349_9999 : 24'd49_9999;
    always_ff @(posedge sys_clk, negedge sys_rst_n) begin
        if (!sys_rst_n) counter <= 24'd0;
        else if (counter < count_max)  // 0.5s delay
            counter <= counter + 1'b1;
        else counter <= 24'd0;
    end

    always_ff @(posedge sys_clk, negedge sys_rst_n) begin
        if (!sys_rst_n) led_tmp <= 6'b111110;
        else if (counter == count_max)  // 0.5s delay
            led_tmp[5:0] <= {led_tmp[4:0], led_tmp[5]};
        else led_tmp <= led_tmp;
    end
*/
    //assign led = led_tmp;

endmodule

