
module mem_uart_ip (
    input clk,
    input resetn,
    input ser_rx,
    input mem_s_valid,
    input [31:0] mem_s_addr,
    input [31:0] mem_s_wdata,
    input [3:0] mem_s_wstrb,
    output ser_tx,
    output mem_s_ready,
    output [31:0] mem_s_rdata
);

    logic [2:0] mem_wadr, mem_radr;
    logic [7:0] mem_wdata, mem_rdata;
    logic mem_w_en, mem_r_en;
    logic mem_r_en_1T, mem_r_en_2T, mem_r_en_3T;
    logic mem_r_en_raise_1T, mem_r_en_raise_2T, mem_r_en_raise_3T;

    assign mem_w_en = mem_s_valid && (mem_s_wstrb != 4'h0);
    // レジスタアクセスが32Byte単位のため、IP用のアドレスに変更
    assign mem_wadr = mem_s_addr[4:2];
    assign mem_wdata = mem_s_wdata[7:0];

    assign mem_r_en = mem_s_valid && (mem_s_wstrb == 4'h0);
    assign mem_r_en_raise = mem_r_en & ~mem_r_en_1T;
    // レジスタアクセスが32Byte単位のため、IP用のアドレスに変更
    assign mem_radr = mem_s_addr[4:2];

    always_ff @(posedge clk, negedge resetn) begin
        if (!resetn) begin
            mem_r_en_1T <= 1'd0;
            mem_r_en_2T <= 1'd0;
            mem_r_en_3T <= 1'd0;
        end else begin
            mem_r_en_1T <= mem_r_en;
            mem_r_en_2T <= mem_r_en_1T;
            mem_r_en_3T <= mem_r_en_2T;
        end
    end

    always_ff @(posedge clk, negedge resetn) begin
        if (!resetn) begin
            mem_r_en_raise_1T <= 1'd0;
            mem_r_en_raise_2T <= 1'd0;
            mem_r_en_raise_3T <= 1'd0;
        end else begin
            mem_r_en_raise_1T <= mem_r_en_raise;
            mem_r_en_raise_2T <= mem_r_en_raise_1T;
            mem_r_en_raise_3T <= mem_r_en_raise_2T;
        end
    end

    assign mem_s_rdata = {24'd0, mem_rdata};
    assign mem_s_ready = mem_r_en_raise_3T | mem_w_en;

    uart_ip_Top m_uart_ip_Top (
        .I_CLK(clk),  //input I_CLK
        .I_RESETN(resetn),  //input I_RESETN
        .I_TX_EN(mem_w_en),  //input I_TX_EN
        .I_WADDR(mem_wadr),  //input [2:0] I_WADDR
        .I_WDATA(mem_wdata),  //input [7:0] I_WDATA
        .I_RX_EN(mem_r_en_raise),  //input I_RX_EN
        .I_RADDR(mem_radr),  //input [2:0] I_RADDR
        .O_RDATA(mem_rdata),  //output [7:0] O_RDATA
        .SIN(ser_rx),  //input SIN
        .RxRDYn(),  //output RxRDYn
        .SOUT(ser_tx),  //output SOUT
        .TxRDYn(),  //output TxRDYn
        .DDIS(),  //output DDIS
        .INTR(),  //output INTR
        .DCDn(1'b0),  //input DCDn
        .CTSn(1'b0),  //input CTSn
        .DSRn(1'b0),  //input DSRn
        .RIn(1'b0),  //input RIn
        .DTRn(),  //output DTRn
        .RTSn()  //output RTSn
    );


endmodule
