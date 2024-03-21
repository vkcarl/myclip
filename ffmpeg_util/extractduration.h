#ifndef EXTRACTDURATION_H
#define EXTRACTDURATION_H

#include <QString>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersrc.h"
#include "libavfilter/buffersink.h"
#include "libavutil/bprint.h"
}

class MediaDurationTool {
public:
    MediaDurationTool();
    static int extractDuration(const QString &videoPath, int64_t *duration, double *fps);
};

#endif // EXTRACTDURATION_H
