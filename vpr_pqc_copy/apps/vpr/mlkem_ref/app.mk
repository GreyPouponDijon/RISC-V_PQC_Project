VPR_MLKEM = 1

ALG_SRC_C += cbd.c fips202.c indcpa.c kem.c ntt.c poly.c polyvec.c reduce.c verify.c symmetric-shake.c randombytes.c
VPR_SRC_C += $(addprefix $(VPR_APP_DIR)/, $(ALG_SRC_C))
TEST_SRC_C += test_kyber.c cpucycles.c speed_print.c
VPR_SRC_C += $(addprefix $(VPR_APP_DIR)/test/, $(TEST_SRC_C))
#VPR_SRC_S += $(VPR_APP_DIR)/*.S
#VPR_SRC_S += $(VPR_APP_DIR)/test/*.S
#VPR_SRC_H += $(VPR_APP_DIR)/*.h
#VPR_SRC_H += $(VPR_APP_DIR)/test/*.h
