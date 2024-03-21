#ifndef FRAMERATEMANAGER_H
#define FRAMERATEMANAGER_H

#include "imf/imfcommon.h"
class FrameRateManager {
public:
    static void changeEditRate(const EditRate& e) {
        max_edit_rate_in_all_file_ = e;
    }
    static EditRate& getEditRate() {
        return max_edit_rate_in_all_file_;
    }
    static EditRate max_edit_rate_in_all_file_;
};

#endif // FRAMERATEMANAGER_H
