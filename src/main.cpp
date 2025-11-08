#include "main.h"
#include "ui.h"
#include "ddcutil.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    DDCA_Status rc;
    DDCA_Display_Info_List *dlist = NULL;
    DDCA_Display_Handle dh = NULL;

    // Initialize ddcutil
    rc = ddca_init("--ddc", DDCA_SYSLOG_ERROR, DDCA_INIT_OPTIONS_NONE);
    if (rc != 0) {
        fprintf(stderr, "Error initializing ddcutil: %s\n", ddca_rc_name(rc));
        return 1;
    }

    // Get display list
    rc = ddca_get_display_info_list2(false, &dlist);
    if (rc != 0 || dlist->ct == 0) {
        fprintf(stderr, "No displays found.\n");
        ddca_free_display_info_list(dlist);
        return 1;
    }

    // Open first display
    DDCA_Display_Ref dref = dlist->info[0].dref;
    rc = ddca_open_display2(dref, false, &dh);
    if (rc != 0) {
        fprintf(stderr, "Failed to open display: %s\n", ddca_rc_name(rc));
        ddca_free_display_info_list(dlist);
        return 1;
    }

    // Run Qt UI
    int result = uiopen(argc, argv, dh);

    // Cleanup
    ddca_close_display(dh);
    ddca_free_display_info_list(dlist);

    return result;
}
