#include <string>
#include <deque>

#include <fmt/format.h>

#include "CxxPtr/GlibPtr.h"
#include "CxxPtr/GstRtspServerPtr.h"


#define BARS  "bars"
#define WHITE "white"
#define BLACK "black"
#define RED   "red"
#define GREEN "green"
#define BLUE  "blue"


int main(int argc, char *argv[])
{
    const std::string h264PipelineTemplate =
        "( videotestsrc pattern={} ! "
        "x264enc ! video/x-h264, profile=baseline ! "
        "rtph264pay name=pay0 pt=96 config-interval=-1 "
        "audiotestsrc ! opusenc ! rtpopuspay name=pay1 pt=97 )";

    const std::string vp8PipelineTemplate =
        "( videotestsrc pattern={} ! "
        "vp8enc ! rtpvp8pay name=pay0 pt=96 "
        "audiotestsrc ! opusenc ! rtpopuspay name=pay1 pt=97 )";

    const std::deque<std::pair<std::string, std::string>> createMountPoints = {
        {BARS, "smpte100"},
        {WHITE, "white"},
        {BLACK, "black"},
        {RED, "red"},
        {GREEN, "green"},
        {BLUE, "blue"},
    };

    gst_init(&argc, &argv);

    GstRTSPServerPtr staticServer(gst_rtsp_server_new());
    GstRTSPServer* server = staticServer.get();
    if(!server) {
        GST_ERROR("Fail to create rtsp server");
        return -1;
    }

    GstRTSPMountPointsPtr mountPointsPtr(gst_rtsp_mount_points_new());
    GstRTSPMountPoints* mountPoints = mountPointsPtr.get();
    if(!server) {
        GST_ERROR("Fail to create mount points");
        return -1;
    }

    gst_rtsp_server_set_mount_points(server, mountPoints);

    // h264
    for(const auto& mountPoint: createMountPoints) {
        GstRTSPMediaFactory* factory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_transport_mode(
            factory, GST_RTSP_TRANSPORT_MODE_PLAY);
        gst_rtsp_media_factory_set_launch(factory,
            fmt::format(h264PipelineTemplate, mountPoint.second).c_str());
        gst_rtsp_media_factory_set_shared(factory, TRUE);
        gst_rtsp_mount_points_add_factory(
            mountPoints,
            ("/" + mountPoint.first).c_str(),
            factory);
    }

    // vp8
    for(const auto& mountPoint: createMountPoints) {
        GstRTSPMediaFactory* factory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_transport_mode(
            factory, GST_RTSP_TRANSPORT_MODE_PLAY);
        gst_rtsp_media_factory_set_launch(factory,
            fmt::format(vp8PipelineTemplate, mountPoint.second).c_str());
        gst_rtsp_media_factory_set_shared(factory, TRUE);
        gst_rtsp_mount_points_add_factory(
            mountPoints,
            ("/" + mountPoint.first + "-vp8").c_str(),
            factory);
    }

    GMainLoopPtr loopPtr(g_main_loop_new(nullptr, FALSE));
    GMainLoop* loop = loopPtr.get();

    gst_rtsp_server_attach(server, nullptr);

    g_main_loop_run(loop);

    return 0;
}
