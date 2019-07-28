#include "CxxPtr/GlibPtr.h"
#include "CxxPtr/GstRtspServerPtr.h"

#define BARS  "/bars"
#define WHITE "/white"
#define BLACK "/black"
#define RED   "/red"
#define GREEN "/green"
#define BLUE  "/blue"


int main(int argc, char *argv[])
{
    gst_init(&argc, &argv);

    GstRTSPServerPtr staticServer(gst_rtsp_server_new());
    GstRTSPMountPointsPtr mountPointsPtr(gst_rtsp_mount_points_new());

    GstRTSPServer* server = staticServer.get();
    GstRTSPMountPoints* mountPoints = mountPointsPtr.get();

    gst_rtsp_server_set_mount_points(server, mountPoints);

    {
        GstRTSPMediaFactory* barsFactory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_transport_mode(
            barsFactory, GST_RTSP_TRANSPORT_MODE_PLAY);
        gst_rtsp_media_factory_set_launch(barsFactory,
            "( videotestsrc pattern=smpte100 ! "
            "x264enc ! video/x-h264, profile=baseline ! "
            "rtph264pay name=pay0 pt=96 config-interval=-1 )");
        gst_rtsp_media_factory_set_shared(barsFactory, TRUE);
        gst_rtsp_mount_points_add_factory(mountPoints, BARS, barsFactory);
    }

    {
        GstRTSPMediaFactory* whiteScreenFactory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_transport_mode(
            whiteScreenFactory, GST_RTSP_TRANSPORT_MODE_PLAY);
        gst_rtsp_media_factory_set_launch(whiteScreenFactory,
            "( videotestsrc pattern=white ! "
            "x264enc ! video/x-h264, profile=baseline ! "
            "rtph264pay name=pay0 pt=96 config-interval=-1 )");
        gst_rtsp_media_factory_set_shared(whiteScreenFactory, TRUE);
        gst_rtsp_mount_points_add_factory(mountPoints, WHITE, whiteScreenFactory);
    }

    {
        GstRTSPMediaFactory* blackScreenFactory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_transport_mode(
            blackScreenFactory, GST_RTSP_TRANSPORT_MODE_PLAY);
        gst_rtsp_media_factory_set_launch(blackScreenFactory,
            "( videotestsrc pattern=black ! "
            "x264enc ! video/x-h264, profile=baseline ! "
            "rtph264pay name=pay0 pt=96 config-interval=-1 )");
        gst_rtsp_media_factory_set_shared(blackScreenFactory, TRUE);
        gst_rtsp_mount_points_add_factory(mountPoints, BLACK, blackScreenFactory);
    }

    {
        GstRTSPMediaFactory* redScreenFactory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_transport_mode(
            redScreenFactory, GST_RTSP_TRANSPORT_MODE_PLAY);
        gst_rtsp_media_factory_set_launch(redScreenFactory,
            "( videotestsrc pattern=red ! "
            "x264enc ! video/x-h264, profile=baseline ! "
            "rtph264pay name=pay0 pt=96 config-interval=-1 )");
        gst_rtsp_media_factory_set_shared(redScreenFactory, TRUE);
        gst_rtsp_mount_points_add_factory(mountPoints, RED, redScreenFactory);
    }

    {
        GstRTSPMediaFactory* greenScreenFactory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_transport_mode(
            greenScreenFactory, GST_RTSP_TRANSPORT_MODE_PLAY);
        gst_rtsp_media_factory_set_launch(greenScreenFactory,
            "( videotestsrc pattern=green ! "
            "x264enc ! video/x-h264, profile=baseline ! "
            "rtph264pay name=pay0 pt=96 config-interval=-1 )");
        gst_rtsp_media_factory_set_shared(greenScreenFactory, TRUE);
        gst_rtsp_mount_points_add_factory(mountPoints, GREEN, greenScreenFactory);
    }

    {
        GstRTSPMediaFactory* blueScreenFactory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_transport_mode(
            blueScreenFactory, GST_RTSP_TRANSPORT_MODE_PLAY);
        gst_rtsp_media_factory_set_launch(blueScreenFactory,
            "( videotestsrc pattern=blue ! "
            "x264enc ! video/x-h264, profile=baseline ! "
            "rtph264pay name=pay0 pt=96 config-interval=-1 )");
        gst_rtsp_media_factory_set_shared(blueScreenFactory, TRUE);
        gst_rtsp_mount_points_add_factory(mountPoints, BLUE, blueScreenFactory);
    }

    GMainLoopPtr loopPtr(g_main_loop_new(nullptr, FALSE));
    GMainLoop* loop = loopPtr.get();

    gst_rtsp_server_attach(server, nullptr);

    g_main_loop_run(loop);
}
