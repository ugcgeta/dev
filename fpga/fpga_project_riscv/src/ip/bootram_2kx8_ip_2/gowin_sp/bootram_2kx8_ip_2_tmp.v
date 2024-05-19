//Copyright (C)2014-2024 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: Template file for instantiation
//Tool Version: V1.9.9.02
//Part Number: GW1NR-LV9QN88PC6/I5
//Device: GW1NR-9
//Device Version: C
//Created Time: Mon May 13 11:19:23 2024

//Change the instance name and port connections to the signal names
//--------Copy here to design--------

    bootram_2kx8_ip_2 your_instance_name(
        .dout(dout_o), //output [7:0] dout
        .clk(clk_i), //input clk
        .oce(oce_i), //input oce
        .ce(ce_i), //input ce
        .reset(reset_i), //input reset
        .wre(wre_i), //input wre
        .ad(ad_i), //input [10:0] ad
        .din(din_i) //input [7:0] din
    );

//--------Copy end-------------------
