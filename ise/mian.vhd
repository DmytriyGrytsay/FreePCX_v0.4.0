library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
library UNISIM;
use UNISIM.VComponents.all;

entity mian is
port ( 
	clk : in  std_logic;
	rst : in  std_logic;
	--ddr2 memory signals
	mpmc_0_DDR2_Clk_pin							: out std_logic_vector (1 downto 0);
	mpmc_0_DDR2_Clk_n_pin 						: out std_logic_vector (1 downto 0);
	mpmc_0_DDR2_CE_pin		 					: out std_logic;
	mpmc_0_DDR2_CS_n_pin 						: out std_logic;
	mpmc_0_DDR2_ODT_pin							: out std_logic;
	mpmc_0_DDR2_CAS_n_pin						: out std_logic;
	mpmc_0_DDR2_RAS_n_pin						: out std_logic;
	mpmc_0_DDR2_WE_n_pin				 			: out std_logic;
	mpmc_0_DDR2_BankAddr_pin					: out std_logic_vector(2 downto 0);
	mpmc_0_DDR2_Addr_pin							: out std_logic_vector(13 downto 0);
	mpmc_0_DDR2_DQ									: inout std_logic_vector(31 downto 0);
	mpmc_0_DDR2_DM_pin							: out std_logic_vector(3 downto 0);
	mpmc_0_DDR2_DQS								: inout std_logic_vector(3 downto 0);
	mpmc_0_DDR2_DQS_n								: inout std_logic_vector(3 downto 0);
	mpmc_0_DDR2_DQS_Div_O_pin					: out std_logic;
	mpmc_0_DDR2_DQS_Div_I_pin					: in std_logic;	
	--nor flash signals
	flash_addr										: out std_logic_vector(0 to 26);
	flash_data										: inout std_logic_vector(0 to 15);
	flash_rpn										: out std_logic;
	flash_cen										: out std_logic;
	flash_oen										: out std_logic;
	flash_wen										: out std_logic;
	flash_busy										: in std_logic;
	--usb host signals
	usb_int											: in std_logic;
	usb_data											: inout std_logic_vector(0 to 15);
	usb_addr											: out std_logic_vector(0 to 1);
	usb_rst											: out std_logic;
	usb_cs											: out std_logic;
	usb_wr											: out std_logic;
	usb_rd											: out std_logic;
	usb_hub_rst										: out std_logic;
	--video processor signals
	video_int										: in std_logic;
	video_data										: inout std_logic_vector(0 to 15);
	video_addr										: out std_logic;
	video_rst										: out std_logic;
	video_cs											: out std_logic;
	video_wr											: out std_logic;
	video_rd											: out std_logic;
	video_hale										: out std_logic;
	--sysace signals
	sysace_addr										: out std_logic_vector(6 downto 0);
	sysace_data										: inout std_logic_vector(15 downto 0);
	sysace_clk										: in std_logic;
	sysace_irq										: in std_logic;
	sysace_oe										: out std_logic;
	sysace_we										: out std_logic;
	sysace_ce										: out std_logic;
 	--gigabit ethernet 0
	fpga_0_Soft_TEMAC_MII_TXD_0_pin				: out std_logic_vector(3 downto 0);			
	fpga_0_Soft_TEMAC_MII_TX_EN_0_pin 			: out std_logic;
	fpga_0_Soft_TEMAC_MII_TX_ER_0_pin			: out std_logic;
	fpga_0_Soft_TEMAC_MII_RXD_0_pin 				: in std_logic_vector(3 downto 0);	
	fpga_0_Soft_TEMAC_MII_RX_DV_0_pin			: in std_logic;
	fpga_0_Soft_TEMAC_MII_RX_ER_0_pin 			: in std_logic;
	fpga_0_Soft_TEMAC_MII_RX_CLK_0_pin 			: in std_logic;
	fpga_0_Soft_TEMAC_MDC_0_pin					: out std_logic;
	fpga_0_Soft_TEMAC_TemacPhy_RST_n_pin 		: out std_logic;
	fpga_0_Soft_TEMAC_MDIO_0						: inout std_logic;
	fpga_0_Soft_TEMAC_MII_TX_CLK_0_pin			: in std_logic;	
	--gigabit ethernet 1
	fpga_1_Soft_TEMAC_MII_TXD_0_pin				: out std_logic_vector(3 downto 0);			
	fpga_1_Soft_TEMAC_MII_TX_EN_0_pin 			: out std_logic;
	fpga_1_Soft_TEMAC_MII_TX_ER_0_pin			: out std_logic;
	fpga_1_Soft_TEMAC_MII_RXD_0_pin 				: in std_logic_vector(3 downto 0);	
	fpga_1_Soft_TEMAC_MII_RX_DV_0_pin			: in std_logic;
	fpga_1_Soft_TEMAC_MII_RX_ER_0_pin 			: in std_logic;
	fpga_1_Soft_TEMAC_MII_RX_CLK_0_pin 			: in std_logic;
	fpga_1_Soft_TEMAC_MDC_0_pin					: out std_logic;
	fpga_1_Soft_TEMAC_TemacPhy_RST_n_pin 		: out std_logic;
	fpga_1_Soft_TEMAC_MDIO_0						: inout std_logic;
	fpga_1_Soft_TEMAC_MII_TX_CLK_0_pin			: in std_logic;		
	--pci arbiter signal 
	pci_req_n			: in std_logic_vector(0 to 3);
	pci_gnt_n			: out std_logic_vector(0 to 3);
	--pci bus signal 
	pci_ad				: inout std_logic_vector (31 downto 0);
	pci_cbe				: inout std_logic_vector (3 downto 0);
	pci_par				: inout std_logic;
	pci_frame_n			: inout std_logic;
	pci_trdy_n			: inout std_logic;
	pci_irdy_n			: inout std_logic;
	pci_stop_n			: inout std_logic;
	pci_devsel_n		: inout std_logic;
	pci_perr_n			: inout std_logic;
	pci_serr_n			: inout std_logic;
	pci_clk				: in std_logic;
	pci_clk_p			: out std_logic_vector(0 to 3);
	pci_int_a			: in std_logic;
	pci_int_b			: in std_logic;
	pci_int_c			: in std_logic;
	pci_int_d			: in std_logic;
	--ac97 codec signals
	ac97_clk				: in std_logic;
	ac97_sync			: out std_logic;
	ac97_reset			: out std_logic;
	ac97_dout			: out std_logic;
	ac97_din				: in std_logic;
	--spi flash signals
	spi_miso				: inout std_logic;
	spi_mosi				: inout std_logic;
	spi_sck				: inout std_logic;
	spi_cs				: inout std_logic;
	--spi conf flash signals
	spi_conf_miso		: inout std_logic;
	spi_conf_mosi		: inout std_logic;
	spi_conf_sck		: inout std_logic;
	spi_conf_cs			: inout std_logic;
	--i2c signals
	i2c_sda				: inout std_logic;
	i2c_scl				: inout std_logic;
	--uart debug signals
	uart0_tx				: out std_logic;
	uart0_rx				: in std_logic;
	--uart debug signals
	uart1_tx				: out std_logic;
	uart1_rx				: in std_logic;
	--uart debug signals
	uart2_tx				: out std_logic;
	uart2_rx				: in std_logic;
	--uart 16550 signals
	uart_ctsn			: in std_logic;
	uart_dcdn			: in std_logic;
	uart_dtrn			: out std_logic;
	uart_dsrn			: in std_logic;
	uart_rtsn			: out std_logic;
	uart_rin				: in std_logic;
	uart_sin				: in std_logic;
	uart_sout			: out std_logic;
	--buzzer signal
	buzzer				: out std_logic;
	--gpio inout signals
	gpio_inout			: inout std_logic_vector (0 to 3);
	--gpio input signals
	gpio_input			: in std_logic_vector (0 to 5);
	--mmc signals							
	mmc_cmd				: inout std_logic;
	mmc_data				: inout std_logic_vector (3 downto 0);
	mmc_clk				: out std_logic;
	mmc_cd				: in std_logic;
	--ps2 signals
	ps2_clk_0			: inout std_logic;
	ps2_data_0			: inout std_logic;
	ps2_clk_1			: inout std_logic;
	ps2_data_1			: inout std_logic
);
end mian;

architecture Behavioral of mian is

	signal ibufg_clk, ibufg_pci_clk		: std_logic;
	signal signal_video_addr : std_logic_vector(0 to 1);
	--signal ibuf_video_int	: std_logic;

	component IBUFG is
		port ( 
			O	: out std_logic;
			I	: in std_logic
	);
	end component; 

	component IBUF is
		port ( 
			O	: out std_logic;
			I	: in std_logic
	);
	end component; 
	
	component OBUFT is
		port ( 
			O	: out std_logic;
			I	: in std_logic;
			T	: in std_logic
	);
	end component; 

	component IOBUF is
		port ( 
			O	: out std_logic;
			I	: in std_logic;
			T	: in std_logic;
			IO : inout std_logic
	);
	end component; 

	
	attribute BOX_TYPE		: string;
	attribute BOX_TYPE of IBUFG : component is "black_box"; 
	attribute BOX_TYPE of IOBUF : component is "black_box"; 
	attribute BOX_TYPE of IBUF : component is "black_box"; 

	component mb is
		port ( 
			--system signals
			fpga_0_clk_1_sys_clk_pin					: in std_logic;
			fpga_0_rst_1_sys_rst_pin					: in std_logic;
			--ddr2 memory signals
			mpmc_0_DDR2_Clk_pin							: out std_logic_vector (1 downto 0);
			mpmc_0_DDR2_Clk_n_pin 						: out std_logic_vector (1 downto 0);
			mpmc_0_DDR2_CE_pin		 					: out std_logic;
			mpmc_0_DDR2_CS_n_pin 						: out std_logic;
			mpmc_0_DDR2_ODT_pin							: out std_logic;
			mpmc_0_DDR2_CAS_n_pin						: out std_logic;
			mpmc_0_DDR2_RAS_n_pin						: out std_logic;
			mpmc_0_DDR2_WE_n_pin				 			: out std_logic;
			mpmc_0_DDR2_BankAddr_pin					: out std_logic_vector(2 downto 0);
			mpmc_0_DDR2_Addr_pin							: out std_logic_vector(13 downto 0);
			mpmc_0_DDR2_DQ									: inout std_logic_vector(31 downto 0);
			mpmc_0_DDR2_DM_pin							: out std_logic_vector(3 downto 0);
			mpmc_0_DDR2_DQS								: inout std_logic_vector(3 downto 0);
			mpmc_0_DDR2_DQS_n								: inout std_logic_vector(3 downto 0);
			mpmc_0_DDR2_DQS_Div_O_pin					: out std_logic;
			mpmc_0_DDR2_DQS_Div_I_pin					: in std_logic;							
			--nor flash signals
			xps_mch_emc_0d_Mem_DQ_pin 					: inout std_logic_vector(0 to 15);
			xps_mch_emc_0d_Mem_A_pin 					: out std_logic_vector(0 to 26);
			xps_mch_emc_0d_Mem_OEN_pin 				: out std_logic;
			xps_mch_emc_0d_Mem_RPN_pin 				: out std_logic;
			xps_mch_emc_0d_Mem_WEN_pin 				: out std_logic;
			xps_mch_emc_0d_Mem_CEN_pin 				: out std_logic;
			--usb host signals
			xps_epc_0_PRH_Rd_n_pin						: out std_logic;
			xps_epc_0_PRH_Wr_n_pin						: out std_logic;
			xps_epc_0_PRH_Data							: inout std_logic_vector(0 to 15);
			xps_epc_0_PRH_CS_n_pin						: out std_logic;
			util_bus_split_0_Out1_pin					: out std_logic_vector(0 to 1);
			usb_int 											: in std_logic;
			--video processor signals
			xps_epc_1_PRH_Data_pin						: inout std_logic_vector(0 to 15);
			xps_epc_1_PRH_Rd_n_pin						: out std_logic;
			xps_epc_1_PRH_Wr_n_pin						: out std_logic;
			xps_epc_1_PRH_CS_n_pin						: out std_logic;
		--	video_int 										: in std_logic;
			util_bus_split_1_Out1_pin					: out std_logic_vector(0 to 1);
			--sysace signals
			xps_sysace_0_SysACE_MPA_pin				: out std_logic_vector(6 downto 0);
			xps_sysace_0_SysACE_MPD_pin				: inout std_logic_vector(15 downto 0);
			xps_sysace_0_SysACE_CLK_pin				: in std_logic;
			xps_sysace_0_SysACE_MPIRQ_pin				: in std_logic;
			xps_sysace_0_SysACE_OEN_pin				: out std_logic;
			xps_sysace_0_SysACE_WEN_pin				: out std_logic;
			xps_sysace_0_SysACE_CEN_pin				: out std_logic;
			--100M ethernet 0
			xps_ll_temac_0_MII_TXD_0_pin				: out std_logic_vector(3 downto 0);			
			xps_ll_temac_0_MII_TX_EN_0_pin 			: out std_logic;
			xps_ll_temac_0_MII_TX_ER_0_pin			: out std_logic;
			xps_ll_temac_0_MII_RXD_0_pin 				: in std_logic_vector(3 downto 0);	
			xps_ll_temac_0_MII_RX_DV_0_pin			: in std_logic;
			xps_ll_temac_0_MII_RX_ER_0_pin 			: in std_logic;
			xps_ll_temac_0_MII_RX_CLK_0_pin 			: in std_logic;
			xps_ll_temac_0_MDC_0_pin					: out std_logic;
			xps_ll_temac_0_TemacPhy_RST_n_pin 		: out std_logic;
			xps_ll_temac_0_MDIO_0						: inout std_logic;
			xps_ll_temac_0_MII_TX_CLK_0_pin			: in std_logic;
			--100M ethernet 1
			xps_ll_temac_1_MII_TXD_0_pin				: out std_logic_vector(3 downto 0);			
			xps_ll_temac_1_MII_TX_EN_0_pin 			: out std_logic;
			xps_ll_temac_1_MII_TX_ER_0_pin			: out std_logic;
			xps_ll_temac_1_MII_RXD_0_pin 				: in std_logic_vector(3 downto 0);	
			xps_ll_temac_1_MII_RX_DV_0_pin			: in std_logic;
			xps_ll_temac_1_MII_RX_ER_0_pin 			: in std_logic;
			xps_ll_temac_1_MII_RX_CLK_0_pin 			: in std_logic;
			xps_ll_temac_1_MDC_0_pin					: out std_logic;
			xps_ll_temac_1_TemacPhy_RST_n_pin 		: out std_logic;
			xps_ll_temac_1_MDIO_0						: inout std_logic;
			xps_ll_temac_1_MII_TX_CLK_0_pin			: in std_logic;
			--pci signals
			plbv46_pci_0_AD 								: inout std_logic_vector(31 downto 0);	
			plbv46_pci_0_CBE								: inout std_logic_vector(3 downto 0);	
			plbv46_pci_0_PAR 								: inout std_logic;
			plbv46_pci_0_FRAME_N 						: inout std_logic;
			plbv46_pci_0_TRDY_N							: inout std_logic;
			plbv46_pci_0_IRDY_N 							: inout std_logic;
			plbv46_pci_0_STOP_N 							: inout std_logic;
			plbv46_pci_0_DEVSEL_N 						: inout std_logic;
			plbv46_pci_0_PERR_N 							: inout std_logic;
			plbv46_pci_0_SERR_N							: inout std_logic;
			plbv46_pci_0_PCLK_pin 						: in std_logic;
			pci_arb_req_n_pin								: in std_logic_vector(0 to 3);
			pci_arb_gnt_n_pin								: out std_logic_vector(0 to 3);
			PCI_INTA_N										: in std_logic;
			PCI_INTB_N										: in std_logic;
			PCI_INTC_N										: in std_logic;
			PCI_INTD_N										: in std_logic;
			--ac97 codec signals
			opb_ac97_controller_ref_0_Sync_pin 			: out std_logic;
			opb_ac97_controller_ref_0_SData_Out_pin 	: out std_logic;
			opb_ac97_controller_ref_0_SData_In_pin 	: in std_logic; 
			opb_ac97_controller_ref_0_Bit_Clk_pin 		: in std_logic; 
			--uart 0
			xps_uartlite_0_RX_pin						: in std_logic; 
			xps_uartlite_0_TX_pin						: out std_logic;
			--uart 1
			xps_uartlite_1_RX_pin						: in std_logic; 
			xps_uartlite_1_TX_pin						: out std_logic;
			--uart 2
			xps_uartlite_2_RX_pin						: in std_logic; 
			xps_uartlite_2_TX_pin						: out std_logic;
			--uart 16550
			xps_uart16550_0_ctsN_pin 					: in std_logic;
			xps_uart16550_0_dcdN_pin					: in std_logic;
			xps_uart16550_0_dtrN_pin					: out std_logic;
			xps_uart16550_0_dsrN_pin					: in std_logic;
			xps_uart16550_0_rtsN_pin					: out std_logic;
			xps_uart16550_0_riN_pin						: in std_logic;
			xps_uart16550_0_sin_pin						: in std_logic;
			xps_uart16550_0_sout_pin					: out std_logic;
			--spi 0
			xps_spi_0_MISO									: inout std_logic;
			xps_spi_0_MOSI									: inout std_logic;
			xps_spi_0_SS 									: inout std_logic;
			xps_spi_0_SCK 									: inout std_logic;
			--spi 1
			xps_spi_1_MISO									: inout std_logic;
			xps_spi_1_MOSI									: inout std_logic;
			xps_spi_1_SS 									: inout std_logic;
			xps_spi_1_SCK 									: inout std_logic;
			--buzzer
			fle_tonegen_0_BuzzerOUT_pin				: out std_logic;
			--gpio inout
			xps_gpio_0_GPIO_IO_pin						: inout std_logic_vector(0 to 3);
			--gpio input
			xps_gpio_0_GPIO2_IO_I_pin					: in std_logic_vector(0 to 5);
			--i2c
			xps_iic_0_Scl									: inout std_logic;
			xps_iic_0_Sda 									: inout std_logic;
			--mmc signals
			xps_sd_if_net_0_SD_protect_pin			: in std_logic; 
			xps_sd_if_net_0_SD_inserted_pin			: in std_logic;
			xps_sd_if_net_0_SD_clk_pin					: out std_logic;
			xps_sd_if_net_0_SD_data_pin				: inout std_logic_vector (3 downto 0);
			xps_sd_if_net_0_SD_cmd_pin					: inout std_logic;
			--ps2 signals
			xps_ps2_0_PS2_1_DATA_pin					: inout std_logic;					
			xps_ps2_0_PS2_1_CLK_pin						: inout std_logic;						
			xps_ps2_0_PS2_2_DATA_pin					: inout std_logic;	
			xps_ps2_0_PS2_2_CLK_pin						: inout std_logic	
	);
	end component;

	

begin

	inst_microblaze_systems: mb
	port map(
			--system signals
			fpga_0_clk_1_sys_clk_pin					=> ibufg_clk,
			fpga_0_rst_1_sys_rst_pin					=> rst,
			--ddr memory signals
--			mpmc_0_DDR2_Clk_pin							=> ddr2_clk_p,
--			mpmc_0_DDR2_Clk_n_pin 						=> ddr2_clk_n,
--			mpmc_0_DDR2_CE_pin		 					=> ddr2_ce,
--			mpmc_0_DDR2_CS_n_pin 						=> ddr2_cs_n,
--			mpmc_0_DDR2_ODT_pin							=> ddr2_odt,
--			mpmc_0_DDR2_CAS_n_pin						=> ddr2_cas_n,
--			mpmc_0_DDR2_RAS_n_pin						=> ddr2_ras_n,
--			mpmc_0_DDR2_WE_n_pin				 			=> ddr2_we_n,
--			mpmc_0_DDR2_BankAddr_pin					=> ddr2_b_addr,
--			mpmc_0_DDR2_Addr_pin							=> ddr2_addr,
--			mpmc_0_DDR2_DQ									=> ddr2_dq,
--			mpmc_0_DDR2_DM_pin							=> ddr2_dm,
--			mpmc_0_DDR2_DQS								=> ddr2_dqs,
--			mpmc_0_DDR2_DQS_n								=> ddr2_dqs_n,
--			mpmc_0_DDR2_DQS_Div_O_pin					=> ddr2_dqs_o,
--			mpmc_0_DDR2_DQS_Div_I_pin					=> ddr2_dqs_i
			
			mpmc_0_DDR2_Clk_pin							=> mpmc_0_DDR2_Clk_pin,
			mpmc_0_DDR2_Clk_n_pin 						=> mpmc_0_DDR2_Clk_n_pin,
			mpmc_0_DDR2_CE_pin		 					=> mpmc_0_DDR2_CE_pin,
			mpmc_0_DDR2_CS_n_pin 						=> mpmc_0_DDR2_CS_n_pin,
			mpmc_0_DDR2_ODT_pin							=> mpmc_0_DDR2_ODT_pin,
			mpmc_0_DDR2_CAS_n_pin						=> mpmc_0_DDR2_CAS_n_pin,
			mpmc_0_DDR2_RAS_n_pin						=> mpmc_0_DDR2_RAS_n_pin,
			mpmc_0_DDR2_WE_n_pin				 			=> mpmc_0_DDR2_WE_n_pin,
			mpmc_0_DDR2_BankAddr_pin					=> mpmc_0_DDR2_BankAddr_pin,
			mpmc_0_DDR2_Addr_pin							=> mpmc_0_DDR2_Addr_pin,
			mpmc_0_DDR2_DQ									=> mpmc_0_DDR2_DQ,
			mpmc_0_DDR2_DM_pin							=> mpmc_0_DDR2_DM_pin,
			mpmc_0_DDR2_DQS								=> mpmc_0_DDR2_DQS,
			mpmc_0_DDR2_DQS_n								=> mpmc_0_DDR2_DQS_n,
			mpmc_0_DDR2_DQS_Div_O_pin					=> mpmc_0_DDR2_DQS_Div_O_pin,
			mpmc_0_DDR2_DQS_Div_I_pin					=> mpmc_0_DDR2_DQS_Div_I_pin,										
			--nor flash signals
			xps_mch_emc_0d_Mem_DQ_pin 					=> flash_data,
			xps_mch_emc_0d_Mem_A_pin 					=> flash_addr,
			xps_mch_emc_0d_Mem_OEN_pin 				=> flash_oen,
			xps_mch_emc_0d_Mem_RPN_pin 				=> flash_rpn,
			xps_mch_emc_0d_Mem_WEN_pin 				=> flash_wen,
			xps_mch_emc_0d_Mem_CEN_pin 				=> flash_cen,
			--usb host signals
			xps_epc_0_PRH_Rd_n_pin						=> usb_rd,
			xps_epc_0_PRH_Wr_n_pin						=> usb_wr,
			xps_epc_0_PRH_Data							=> usb_data,
			xps_epc_0_PRH_CS_n_pin						=> usb_cs,
			util_bus_split_0_Out1_pin					=> usb_addr,
			usb_int 											=> usb_int,
			--video processor signals
			xps_epc_1_PRH_Data_pin						=> video_data,
			xps_epc_1_PRH_Rd_n_pin						=> video_rd,
			xps_epc_1_PRH_Wr_n_pin						=> video_wr,
			xps_epc_1_PRH_CS_n_pin						=> video_cs,
			--video_int 										=> ibuf_video_int,
			util_bus_split_1_Out1_pin					=> signal_video_addr,
			--sysace signals
			xps_sysace_0_SysACE_MPA_pin				=> sysace_addr,
			xps_sysace_0_SysACE_MPD_pin				=> sysace_data,
			xps_sysace_0_SysACE_CLK_pin				=> sysace_clk,
			xps_sysace_0_SysACE_MPIRQ_pin				=> sysace_irq,
			xps_sysace_0_SysACE_OEN_pin				=> sysace_oe,
			xps_sysace_0_SysACE_WEN_pin				=> sysace_we,
			xps_sysace_0_SysACE_CEN_pin				=> sysace_ce,
			--gigabit ethernet 0
			xps_ll_temac_0_MII_TXD_0_pin				=> fpga_0_Soft_TEMAC_MII_TXD_0_pin,		
			xps_ll_temac_0_MII_TX_EN_0_pin 			=> fpga_0_Soft_TEMAC_MII_TX_EN_0_pin,
			xps_ll_temac_0_MII_TX_ER_0_pin			=> fpga_0_Soft_TEMAC_MII_TX_ER_0_pin,
			xps_ll_temac_0_MII_RXD_0_pin 				=> fpga_0_Soft_TEMAC_MII_RXD_0_pin,
			xps_ll_temac_0_MII_RX_DV_0_pin			=> fpga_0_Soft_TEMAC_MII_RX_DV_0_pin,
			xps_ll_temac_0_MII_RX_ER_0_pin 			=> fpga_0_Soft_TEMAC_MII_RX_ER_0_pin,
			xps_ll_temac_0_MII_RX_CLK_0_pin 			=> fpga_0_Soft_TEMAC_MII_RX_CLK_0_pin,
			xps_ll_temac_0_MDC_0_pin					=> fpga_0_Soft_TEMAC_MDC_0_pin,
			xps_ll_temac_0_TemacPhy_RST_n_pin 		=> fpga_0_Soft_TEMAC_TemacPhy_RST_n_pin,
			xps_ll_temac_0_MDIO_0						=> fpga_0_Soft_TEMAC_MDIO_0,
			xps_ll_temac_0_MII_TX_CLK_0_pin			=> fpga_0_Soft_TEMAC_MII_TX_CLK_0_pin,
			--gigabit ethernet 1
			xps_ll_temac_1_MII_TXD_0_pin				=> fpga_1_Soft_TEMAC_MII_TXD_0_pin,		
			xps_ll_temac_1_MII_TX_EN_0_pin 			=> fpga_1_Soft_TEMAC_MII_TX_EN_0_pin,
			xps_ll_temac_1_MII_TX_ER_0_pin			=> fpga_1_Soft_TEMAC_MII_TX_ER_0_pin,
			xps_ll_temac_1_MII_RXD_0_pin 				=> fpga_1_Soft_TEMAC_MII_RXD_0_pin,
			xps_ll_temac_1_MII_RX_DV_0_pin			=> fpga_1_Soft_TEMAC_MII_RX_DV_0_pin,
			xps_ll_temac_1_MII_RX_ER_0_pin 			=> fpga_1_Soft_TEMAC_MII_RX_ER_0_pin,
			xps_ll_temac_1_MII_RX_CLK_0_pin 			=> fpga_1_Soft_TEMAC_MII_RX_CLK_0_pin,
			xps_ll_temac_1_MDC_0_pin					=> fpga_1_Soft_TEMAC_MDC_0_pin,
			xps_ll_temac_1_TemacPhy_RST_n_pin 		=> fpga_1_Soft_TEMAC_TemacPhy_RST_n_pin,
			xps_ll_temac_1_MDIO_0						=> fpga_1_Soft_TEMAC_MDIO_0,
			xps_ll_temac_1_MII_TX_CLK_0_pin			=> fpga_1_Soft_TEMAC_MII_TX_CLK_0_pin,
			--pci signals
			plbv46_pci_0_AD 								=> pci_ad,
			plbv46_pci_0_CBE								=> pci_cbe,
			plbv46_pci_0_PAR 								=> pci_par,
			plbv46_pci_0_FRAME_N 						=> pci_frame_n,
			plbv46_pci_0_TRDY_N							=> pci_trdy_n,
			plbv46_pci_0_IRDY_N 							=> pci_irdy_n,
			plbv46_pci_0_STOP_N 							=> pci_stop_n,
			plbv46_pci_0_DEVSEL_N 						=> pci_devsel_n,
			plbv46_pci_0_PERR_N 							=> pci_perr_n,
			plbv46_pci_0_SERR_N							=> pci_serr_n,
			plbv46_pci_0_PCLK_pin 						=> ibufg_pci_clk,
			pci_arb_req_n_pin								=> pci_req_n,
			pci_arb_gnt_n_pin								=> pci_gnt_n,
			PCI_INTA_N										=> pci_int_a,
			PCI_INTB_N										=> pci_int_b,
			PCI_INTC_N										=> pci_int_c,
			PCI_INTD_N										=> pci_int_d,

			opb_ac97_controller_ref_0_Sync_pin 			=> ac97_sync,
			opb_ac97_controller_ref_0_SData_Out_pin 	=> ac97_dout,
			opb_ac97_controller_ref_0_SData_In_pin 	=> ac97_din,
			opb_ac97_controller_ref_0_Bit_Clk_pin 		=> ac97_clk,
			xps_uartlite_0_RX_pin						=> uart0_rx,
			xps_uartlite_0_TX_pin						=> uart0_tx,
			xps_spi_0_MISO									=> spi_miso,
			xps_spi_0_MOSI									=> spi_mosi,
			xps_spi_0_SS 									=> spi_cs,
			xps_spi_0_SCK 									=> spi_sck,
			xps_iic_0_Scl									=> i2c_scl,
			xps_iic_0_Sda 									=> i2c_sda,
			--uart 1
			xps_uartlite_1_RX_pin						=> uart1_rx,
			xps_uartlite_1_TX_pin						=> uart1_tx,
			--uart 2
			xps_uartlite_2_RX_pin						=> uart2_rx,
			xps_uartlite_2_TX_pin						=> uart2_tx,
			--uart 16550		
			xps_uart16550_0_ctsN_pin 					=> uart_ctsn,
			xps_uart16550_0_dcdN_pin					=> uart_dcdn,
			xps_uart16550_0_dtrN_pin					=> uart_dtrn,
			xps_uart16550_0_dsrN_pin					=> uart_dsrn,
			xps_uart16550_0_rtsN_pin					=> uart_rtsn,
			xps_uart16550_0_riN_pin						=> uart_rin,
			xps_uart16550_0_sin_pin						=> uart_sin,
			xps_uart16550_0_sout_pin					=> uart_sout,
			--spi 1
			xps_spi_1_MISO									=> spi_conf_miso,
			xps_spi_1_MOSI									=> spi_conf_mosi,
			xps_spi_1_SS 									=> spi_conf_sck,
			xps_spi_1_SCK 									=> spi_conf_cs,
			--buzzer
			fle_tonegen_0_BuzzerOUT_pin				=> buzzer,
			--gpio inout
			xps_gpio_0_GPIO_IO_pin						=> gpio_inout,
			--gpio input
			xps_gpio_0_GPIO2_IO_I_pin					=> gpio_input,	
			--mmc signals
			xps_sd_if_net_0_SD_protect_pin			=> '0',
			xps_sd_if_net_0_SD_inserted_pin			=> not mmc_cd,
			xps_sd_if_net_0_SD_clk_pin					=> mmc_clk,
			xps_sd_if_net_0_SD_data_pin				=> mmc_data,
			xps_sd_if_net_0_SD_cmd_pin					=> mmc_cmd,
			--ps2 signals
			xps_ps2_0_PS2_1_DATA_pin					=> ps2_data_0,					
			xps_ps2_0_PS2_1_CLK_pin						=> ps2_clk_0,					
			xps_ps2_0_PS2_2_DATA_pin					=> ps2_data_1,
			xps_ps2_0_PS2_2_CLK_pin						=> ps2_clk_1
			
	);		

	inst_IBUFG_main_clk: IBUFG
		port map (
			O	=> ibufg_clk,
			I	=> clk
	);

	inst_IBUFG_pci_clk: IBUFG
		port map (
			O	=> ibufg_pci_clk,
			I	=> pci_clk
	);

	pci_clk_p(0)	<= ibufg_pci_clk;
	pci_clk_p(1)	<= ibufg_pci_clk;
	pci_clk_p(2)	<= ibufg_pci_clk;
	pci_clk_p(3)	<= ibufg_pci_clk;

	ac97_reset 	<= '1';
	usb_rst 		<= '1';
	usb_hub_rst	<= '1';
	video_rst	<= '1';
	video_addr	<= signal_video_addr(0);
	video_hale	<= '0';
	
end Behavioral;
