#include "ddcutil.h"

// Get current brightness (0–100)
int get_brightness(DDCA_Display_Handle dh) {
    DDCA_Status rc;
    DDCA_Non_Table_Vcp_Value val;

    rc = ddca_get_non_table_vcp_value(dh, VCP_BRIGHTNESS, &val);
    if (rc != 0) {
        fprintf(stderr, "Error: ddca_get_non_table_vcp_value() failed (%d: %s)\n",
                rc, ddca_rc_name(rc));
        return -1;
    }

    uint16_t max = (val.mh << 8) | val.ml;
    uint16_t cur = (val.sh << 8) | val.sl;
    int brightness = (int)((double)cur / max * 100.0);
    return brightness;
}

// Set brightness (0–100)
int set_brightness(DDCA_Display_Handle dh, int percent) {
    if (percent < 0 || percent > 100) {
        fprintf(stderr, "Error: Brightness percent must be 0–100\n");
        return -1;
    }

    DDCA_Non_Table_Vcp_Value val;
    DDCA_Status rc;

    rc = ddca_get_non_table_vcp_value(dh, VCP_BRIGHTNESS, &val);
    if (rc != 0) {
        fprintf(stderr, "Error: ddca_get_non_table_vcp_value() failed (%d: %s)\n",
                rc, ddca_rc_name(rc));
        return -1;
    }

    uint16_t max = (val.mh << 8) | val.ml;
    uint16_t new_val = (uint16_t)((percent / 100.0) * max);

    rc = ddca_set_non_table_vcp_value(dh, VCP_BRIGHTNESS,
                                      (new_val >> 8) & 0xFF, new_val & 0xFF);
    if (rc != 0) {
        fprintf(stderr, "Error: ddca_set_non_table_vcp_value() failed (%d: %s)\n",
                rc, ddca_rc_name(rc));
        return -1;
    }

    return 0;
}

