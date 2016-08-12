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
--	ddr2_clk_n			: out std_logic_vector (1 downto 0);
--	ddr2_clk_p			: out std_logic_vector (1 downto 0);
--	ddr2_ce				: out std_logic;
--	ddr2_cs_n			: out std_logic;	
--	ddr2_cas_n			: out std_logic;
--	ddr2_ras_n			: out std_logic;
--	ddr2_we_n			: out std_logic;
--	ddr2_b_addr			: out std_logic_vector (2 downto 0);
--	ddr2_addr			: out std_logic_vector (13 downto 0);
--	ddr2_dq				: inout std_logic_vector (31 downto 0);
--	ddr2_dm				: out std_logic_vector (3 downto 0);
--	ddr2_dqs				: inout std_logic_vector (3 downto 0);
--	ddr2_dqs_n			: inout std_logic_vector (3 downto 0);
--	ddr2_dqs_i			: in std_logic;
--	ddr2_dqs_o			: out std_logic;
--	ddr2_odt				: out std_logic
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
	pci_req_n			: in std_logic_vector(0 to 2);
	pci_gnt_n			: out std_logic_vector(0 to 2);
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
	--i2c signals
	i2c_sda				: inout std_logic;
	i2c_scl				: inout std_logic;
	--uart debug signals
	uart0_tx				: out std_logic;
	uart0_rx				: in std_logic;
	--uart 1 signals
	uart1_tx				: out std_logic;
	uart1_rx				: in std_logic;
	--uart 2 signals
	uart2_tx				: out std_logic;
	uart2_rx				: in std_logic;
	--mmc signals							
	mmc_cmd				: inout std_logic;
	mmc_data				: inout std_logic_vector (3 downto 0);
	mmc_clk				: out std_logic;
	--ps2 signals
	ps2_clk_0			: inout std_logic;
	ps2_data_0			: inout std_logic;
	ps2_clk_1			: inout std_logic;
	ps2_data_1			: inout std_logic
);
end mian;

architecture Behavioral of mian is

	signal ibufg_clk		: std_logic;

	component IBUFG is
		port ( 
			O	: out std_logic;
			I	: in std_logic
	);
	end component; 

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
			pci_arb_req_n_pin								: in std_logic_vector(0 to 2);
			pci_arb_gnt_n_pin								: out std_logic_vector(0 to 2);
			
			opb_ac97_controller_ref_0_Sync_pin 			: out std_logic;
			opb_ac97_controller_ref_0_SData_Out_pin 	: out std_logic;
			opb_ac97_controller_ref_0_SData_In_pin 	: in std_logic; 
			opb_ac97_controller_ref_0_Bit_Clk_pin 		: in std_logic; 
			xps_uartlite_0_RX_pin						: in std_logic; 
			xps_uartlite_0_TX_pin						: out std_logic;
			
			xps_uartlite_1_RX_pin						: in std_logic; 
			xps_uartlite_1_TX_pin						: out std_logic;
			
			xps_uartlite_2_RX_pin						: in std_logic; 
			xps_uartlite_2_TX_pin						: out std_logic;
			
			xps_spi_0_MISO									: inout std_logic;
			xps_spi_0_MOSI									: inout std_logic;
			xps_spi_0_SS 									: inout std_logic;
			xps_spi_0_SCK 									: inout std_logic;
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

	attribute BOX_TYPE		: string;
	attribute BOX_TYPE of IBUFG : component is "black_box"; 

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
			plbv46_pci_0_PCLK_pin 						=> pci_clk,
			pci_arb_req_n_pin								=> pci_req_n,
			pci_arb_gnt_n_pin								=> pci_gnt_n,

			opb_ac97_controller_ref_0_Sync_pin 			=> ac97_sync,
			opb_ac97_controller_ref_0_SData_Out_pin 	=> ac97_dout,
			opb_ac97_controller_ref_0_SData_In_pin 	=> ac97_din,
			opb_ac97_controller_ref_0_Bit_Clk_pin 		=> ac97_clk,
			xps_uartlite_0_RX_pin						=> uart0_rx,
			xps_uartlite_0_TX_pin						=> uart0_tx,
			
			xps_uartlite_1_RX_pin						=> uart1_rx,
			xps_uartlite_1_TX_pin						=> uart1_tx,
			
			xps_uartlite_2_RX_pin						=> uart2_rx,
			xps_uartlite_2_TX_pin						=> uart2_tx,
			
			xps_spi_0_MISO									=> spi_miso,
			xps_spi_0_MOSI									=> spi_mosi,
			xps_spi_0_SS 									=> spi_cs,
			xps_spi_0_SCK 									=> spi_sck,
			xps_iic_0_Scl									=> i2c_scl,
			xps_iic_0_Sda 									=> i2c_sda,			
			--mmc signals
			xps_sd_if_net_0_SD_protect_pin			=> '0',
			xps_sd_if_net_0_SD_inserted_pin			=> '1',
			xps_sd_if_net_0_SD_clk_pin					=> mmc_clk,
			xps_sd_if_net_0_SD_data_pin				=> mmc_data,
			xps_sd_if_net_0_SD_cmd_pin					=> mmc_cmd,
			--ps2 signals
			xps_ps2_0_PS2_1_DATA_pin					=> ps2_data_0,					
			xps_ps2_0_PS2_1_CLK_pin						=> ps2_clk_0,					
			xps_ps2_0_PS2_2_DATA_pin					=> ps2_data_1,
			xps_ps2_0_PS2_2_CLK_pin						=> ps2_clk_1
			
	);		

	inst_IBUFG: IBUFG
		port map (
			O	=> ibufg_clk,
			I	=> clk
	);

	ac97_reset <= '1';

end Behavioral;

