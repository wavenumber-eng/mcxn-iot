#include <zephyr/kernel.h>
#include <zephyr/logging/log_backend.h>
#include <zephyr/logging/log_output.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <sys/types.h>
#include <string.h>

/* Get the base address and size of the OCRAM2 overlay region */
#define OCRAM2_OVERLAY_NODE DT_NODELABEL(ocram2_overlay)
#define OCRAM2_BASE_ADDRESS DT_REG_ADDR(OCRAM2_OVERLAY_NODE)

/* Define a buffer in the OCRAM2 overlay region */
#define LOG_BUFFER_SIZE 4096
#define MAX_LOG_MSG_LENGTH 128

typedef struct {
    uint32_t write_index;
    uint32_t read_index;
    uint8_t buffer[LOG_BUFFER_SIZE];
} shared_log_buffer_t;

volatile shared_log_buffer_t *shared_memory = (shared_log_buffer_t *)OCRAM2_BASE_ADDRESS;

/* Output function to write formatted log messages to the shared memory buffer */
static int log_output_func(uint8_t *data, size_t length, void *ctx)
{
    if((shared_memory->write_index + length) >= LOG_BUFFER_SIZE) {
        shared_memory->write_index = 0;
    }

    memcpy(&shared_memory->buffer[shared_memory->write_index], data, length);
    shared_memory->write_index += length;

    return length;
}

/* Define the log_output structure */
LOG_OUTPUT_DEFINE(log_output, log_output_func, NULL, 0);

static void custom_backend_log_process(const struct log_backend *const backend,
                   union log_msg_generic *msg)
{
    uint32_t flags = LOG_OUTPUT_FLAG_FORMAT_TIMESTAMP;

    log_output_msg_process(&log_output, &msg->log, flags);
}

static void custom_backend_log_panic(const struct log_backend *const backend)
{
    const char *panic_marker = "PANIC_OCCURRED\n";
    size_t marker_len = strlen(panic_marker);

    if ((shared_memory->write_index + marker_len) >= LOG_BUFFER_SIZE) {
        shared_memory->write_index = 0;  // Wrap around if there is no space left
    }

    memcpy(&shared_memory->buffer[shared_memory->write_index], panic_marker, marker_len);
    shared_memory->write_index += marker_len;
}

static void custom_backend_log_init(const struct log_backend *const backend)
{
    printk("Custom backend log init\n");
    shared_memory->write_index = 0;
    shared_memory->read_index = 0;
}

static const struct log_backend_api custom_backend_log_api = {
    .process = custom_backend_log_process,
    .init = custom_backend_log_init,
    .panic = custom_backend_log_panic
};

LOG_BACKEND_DEFINE(custom_backend_log, custom_backend_log_api, true);

const struct log_backend *custom_log_backend_get(void)
{
    return &custom_backend_log;
}