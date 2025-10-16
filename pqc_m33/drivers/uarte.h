
void hal_uarte_init(void);

uint32_t hal_uarte_char_write(uint8_t ch);

uint32_t hal_uarte_char_read(uint8_t * ch);

uint32_t hal_uarte_string_dma_write(const uint8_t * const p_buffer, uint32_t len);

