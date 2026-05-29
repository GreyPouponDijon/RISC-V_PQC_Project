CM33_MLKEM = 1

ALG_SRC_C += cbd.c fips202.c indcpa.c kem.c ntt.c poly.c polyvec.c reduce.c verify.c symmetric-shake.c randombytes.c nrf_config.c
CM33_SRC_C += $(addprefix $(CM33_APP_DIR)/, $(ALG_SRC_C))
TEST_SRC_C += test_speed.c cpucycles.c speed_print.c
CM33_SRC_C += $(addprefix $(CM33_APP_DIR)/test/, $(TEST_SRC_C))
#CM33_SRC_S += $(CM33_APP_DIR)/*.S
#CM33_SRC_S += $(CM33_APP_DIR)/test/*.S
#CM33_SRC_H += $(CM33_APP_DIR)/*.h
#CM33_SRC_H += $(CM33_APP_DIR)/test/*.h
