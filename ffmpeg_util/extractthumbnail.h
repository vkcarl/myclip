#ifndef EXTRACTTHUMBNAIL_H
#define EXTRACTTHUMBNAIL_H
#include <QString>
#include <QPixmap>
#include "extractduration.h"

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersrc.h"
#include "libavfilter/buffersink.h"
#include "libavutil/bprint.h"
}

class ThumbnailTool {
public:
    ThumbnailTool();
    static int extractThumbnail(const QString &videoPath, QPixmap **vedioPixmap, int64_t start);
};
#endif
