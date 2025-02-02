#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *chipname = "gpiochip0"; // GPIO chip name
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int line_num = 27; // GPIO pin number (e.g., GPIO27)
    int value;

    // Open the GPIO chip
    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("Error opening GPIO chip");
        return 1;
    }

    // Open the GPIO line
    line = gpiod_chip_get_line(chip, line_num);
    if (!line) {
        perror("Error getting GPIO line");
        gpiod_chip_close(chip);
        return 1;
    }

    // Request the line as input
    if (gpiod_line_request_input(line, "read-gpio") < 0) {
        perror("Error requesting GPIO line as input");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return 1;
    }

    // Read the GPIO value
    value = gpiod_line_get_value(line);
    if (value < 0) {
        perror("Error reading GPIO value");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return 1;
    }

    printf("GPIO %d value: %d\n", line_num, value);

    // Release the line and close the chip
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return 0;
}
