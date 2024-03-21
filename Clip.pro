QT       += core gui
QT += multimedia
QT += multimediawidgets
QT += quickwidgets
QT += qml
QT += sql
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SOURCES += \
#    abstractproducerwidget.cpp \
#    actions.cpp \
#    autosavefile.cpp \
#    commands/markercommands.cpp \
#    commands/playlistcommands.cpp \
#    commands/timelinecommands.cpp \
#    commands/undohelper.cpp \
#    controllers/filtercontroller.cpp \
#    controllers/scopecontroller.cpp \
#    database.cpp \
#    dialogs/actionsdialog.cpp \
#    dialogs/addencodepresetdialog.cpp \
#    dialogs/alignaudiodialog.cpp \
#    dialogs/alignmentarray.cpp \
#    dialogs/bitratedialog.cpp \
#    dialogs/customprofiledialog.cpp \
#    dialogs/durationdialog.cpp \
#    dialogs/editmarkerdialog.cpp \
#    dialogs/filedatedialog.cpp \
#    dialogs/listselectiondialog.cpp \
#    dialogs/longuitask.cpp \
#    dialogs/multifileexportdialog.cpp \
#    dialogs/resourcedialog.cpp \
#    dialogs/saveimagedialog.cpp \
#    dialogs/slideshowgeneratordialog.cpp \
#    dialogs/systemsyncdialog.cpp \
#    dialogs/textviewerdialog.cpp \
#    dialogs/transcodedialog.cpp \
#    dialogs/unlinkedfilesdialog.cpp \
#    docks/encodedock.cpp \
#    docks/filtersdock.cpp \
#    docks/jobsdock.cpp \
#    docks/keyframesdock.cpp \
#    docks/markersdock.cpp \
#    docks/notesdock.cpp \
#    docks/playlistdock.cpp \
#    docks/recentdock.cpp \
#    docks/scopedock.cpp \
#    docks/timelinedock.cpp \
#    jobqueue.cpp \
#    jobs/abstractjob.cpp \
#    jobs/bitrateviewerjob.cpp \
#    jobs/encodejob.cpp \
#    jobs/ffmpegjob.cpp \
#    jobs/ffprobejob.cpp \
#    jobs/gopro2gpxjob.cpp \
#    jobs/meltjob.cpp \
#    jobs/postjobaction.cpp \
#    jobs/qimagejob.cpp \
#    jobs/videoqualityjob.cpp \
#    main.cpp \
#    clipmain.cpp \
#    mainwindow.cpp \
#    mltcontroller.cpp \
#    mltxmlchecker.cpp \
#    models/actionsmodel.cpp \
#    models/alignclipsmodel.cpp \
#    models/attachedfiltersmodel.cpp \
#    models/audiolevelstask.cpp \
#    models/keyframesmodel.cpp \
#    models/markersmodel.cpp \
#    models/metadatamodel.cpp \
#    models/motiontrackermodel.cpp \
#    models/multitrackmodel.cpp \
#    models/playlistmodel.cpp \
#    models/resourcemodel.cpp \
#    openotherdialog.cpp \
#    player.cpp \
#    playslider.cpp \
#    proxymanager.cpp \
#    qmltypes/colordialog.cpp \
#    qmltypes/colorpickeritem.cpp \
#    qmltypes/colorwheelitem.cpp \
#    qmltypes/filedialog.cpp \
#    qmltypes/fontdialog.cpp \
#    qmltypes/messagedialog.cpp \
#    qmltypes/qmlapplication.cpp \
#    qmltypes/qmleditmenu.cpp \
#    qmltypes/qmlfile.cpp \
#    qmltypes/qmlfilter.cpp \
#    qmltypes/qmlmarkermenu.cpp \
#    qmltypes/qmlmetadata.cpp \
#    qmltypes/qmlproducer.cpp \
#    qmltypes/qmlprofile.cpp \
#    qmltypes/qmlrichtext.cpp \
#    qmltypes/qmlrichtextmenu.cpp \
#    qmltypes/qmlutilities.cpp \
#    qmltypes/qmlview.cpp \
#    qmltypes/thumbnailprovider.cpp \
#    qmltypes/timelineitems.cpp \
#    scrubbar.cpp \
#    settings.cpp \
#    sharedframe.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_audioloudnessscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_audiopeakmeterscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_audiospectrumscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_audiowaveformscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_scopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_videohistogramscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_videorgbparadescopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_videorgbwaveformscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_videovectorscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_videowaveformscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_videozoomscopewidget.cpp \
##    shotcut_autogen/2JHE5F47XL/moc_videozoomwidget.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_actionsdialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_addencodepresetdialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_alignaudiodialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_bitratedialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_customprofiledialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_durationdialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_editmarkerdialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_filedatedialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_listselectiondialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_multifileexportdialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_resourcedialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_saveimagedialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_slideshowgeneratordialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_systemsyncdialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_textviewerdialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_transcodedialog.cpp \
##    shotcut_autogen/2NRMJ5X7RK/moc_unlinkedfilesdialog.cpp \
##    shotcut_autogen/7CL2LH2DRO/moc_filtercontroller.cpp \
##    shotcut_autogen/7CL2LH2DRO/moc_scopecontroller.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_abstractjob.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_bitrateviewerjob.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_encodejob.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_ffmpegjob.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_ffprobejob.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_gopro2gpxjob.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_meltjob.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_qimagejob.cpp \
##    shotcut_autogen/AJN4HOEG3V/moc_videoqualityjob.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_actions.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_autosavefile.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_database.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_jobqueue.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_mainwindow.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_mltcontroller.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_openotherdialog.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_player.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_scrubbar.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_settings.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_transcoder.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_transportcontrol.cpp \
##    shotcut_autogen/EWIEGA46WW/moc_videowidget.cpp \
##    shotcut_autogen/EWIEGA46WW/qrc_resources.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_alsawidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_audiometerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_audioscale.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_avformatproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_avfoundationproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_blipproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_colorbarswidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_colorproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_colorwheel.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_countproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_d3dvideowidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_decklinkproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_directshowvideowidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_docktoolbar.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_editmarkerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_frameratewidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_gdigrabwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_glaxnimateproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_imageproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_isingwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_jackproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_lineeditclear.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_lissajouswidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_lumamixtransition.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_networkproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_newprojectfolder.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_noisewidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_openglvideowidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_plasmawidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_playlisticonview.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_playlistlistview.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_playlisttable.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_producerpreviewwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_pulseaudiowidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_resourcewidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_screenselector.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_servicepresetwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_slideshowgeneratorwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_statuslabelwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_textproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_timelinepropertieswidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_timespinbox.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_toneproducerwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_trackpropertieswidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_video4linuxwidget.cpp \
##    shotcut_autogen/IMAN36LHMA/moc_x11grabwidget.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_actionsmodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_alignclipsmodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_attachedfiltersmodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_keyframesmodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_markersmodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_metadatamodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_motiontrackermodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_multitrackmodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_playlistmodel.cpp \
##    shotcut_autogen/IVK4DJNV27/moc_resourcemodel.cpp \
##    shotcut_autogen/KGPS6WV3FN/qrc_resources.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_colordialog.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_colorpickeritem.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_colorwheelitem.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_filedialog.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_fontdialog.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_messagedialog.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlapplication.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmleditmenu.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlfile.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlfilter.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlmarkermenu.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlmetadata.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlproducer.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlprofile.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlrichtext.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlrichtextmenu.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlutilities.cpp \
##    shotcut_autogen/OJWBM6OTSN/moc_qmlview.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_encodedock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_filtersdock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_jobsdock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_keyframesdock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_markersdock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_notesdock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_playlistdock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_recentdock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_scopedock.cpp \
##    shotcut_autogen/SVAOMNV2MZ/moc_timelinedock.cpp \
##    shotcut_autogen/include/moc_timelinecommands.cpp \
##    shotcut_autogen/mocs_compilation.cpp \
#    spatialmedia/box.cpp \
#    spatialmedia/container.cpp \
#    spatialmedia/mpeg4_container.cpp \
#    spatialmedia/sa3d.cpp \
#    spatialmedia/spatialmedia.cpp \
#    track.cpp \
#    transcoder.cpp \
#    util.cpp \
#    videowidget.cpp \
#    widgets/alsawidget.cpp \
#    widgets/audiometerwidget.cpp \
#    widgets/audioscale.cpp \
#    widgets/avformatproducerwidget.cpp \
#    widgets/avfoundationproducerwidget.cpp \
#    widgets/blipproducerwidget.cpp \
#    widgets/colorbarswidget.cpp \
#    widgets/colorproducerwidget.cpp \
#    widgets/colorwheel.cpp \
#    widgets/countproducerwidget.cpp \
#    widgets/d3dvideowidget.cpp \
#    widgets/decklinkproducerwidget.cpp \
#    widgets/directshowvideowidget.cpp \
#    widgets/docktoolbar.cpp \
#    widgets/editmarkerwidget.cpp \
#    widgets/exportpresetstreeview.cpp \
#    widgets/frameratewidget.cpp \
#    widgets/gdigrabwidget.cpp \
#    widgets/glaxnimateproducerwidget.cpp \
#    widgets/imageproducerwidget.cpp \
#    widgets/isingwidget.cpp \
#    widgets/jackproducerwidget.cpp \
#    widgets/lineeditclear.cpp \
#    widgets/lissajouswidget.cpp \
#    widgets/lumamixtransition.cpp \
#    widgets/networkproducerwidget.cpp \
#    widgets/newprojectfolder.cpp \
#    widgets/noisewidget.cpp \
#    widgets/openglvideowidget.cpp \
#    widgets/plasmawidget.cpp \
#    widgets/playlisticonview.cpp \
#    widgets/playlistlistview.cpp \
#    widgets/playlisttable.cpp \
#    widgets/producerpreviewwidget.cpp \
#    widgets/pulseaudiowidget.cpp \
#    widgets/resourcewidget.cpp \
#    widgets/scopes/audioloudnessscopewidget.cpp \
#    widgets/scopes/audiopeakmeterscopewidget.cpp \
#    widgets/scopes/audiospectrumscopewidget.cpp \
#    widgets/scopes/audiowaveformscopewidget.cpp \
#    widgets/scopes/scopewidget.cpp \
#    widgets/scopes/videohistogramscopewidget.cpp \
#    widgets/scopes/videorgbparadescopewidget.cpp \
#    widgets/scopes/videorgbwaveformscopewidget.cpp \
#    widgets/scopes/videovectorscopewidget.cpp \
#    widgets/scopes/videowaveformscopewidget.cpp \
#    widgets/scopes/videozoomscopewidget.cpp \
#    widgets/scopes/videozoomwidget.cpp \
#    widgets/screenselector.cpp \
#    widgets/servicepresetwidget.cpp \
#    widgets/slideshowgeneratorwidget.cpp \
#    widgets/statuslabelwidget.cpp \
#    widgets/textproducerwidget.cpp \
#    widgets/timelinepropertieswidget.cpp \
#    widgets/timespinbox.cpp \
#    widgets/toneproducerwidget.cpp \
#    widgets/trackpropertieswidget.cpp \
#    widgets/video4linuxwidget.cpp \
#    widgets/x11grabwidget.cpp

#HEADERS += \
#    abstractproducerwidget.h \
#    actions.h \
#    autosavefile.h \
#    clipmain.h \
#    commands/markercommands.h \
#    commands/playlistcommands.h \
#    commands/timelinecommands.h \
#    commands/undohelper.h \
#    controllers/filtercontroller.h \
#    controllers/scopecontroller.h \
#    database.h \
#    dataqueue.h \
#    defaultlayouts.h \
#    dialogs/actionsdialog.h \
#    dialogs/addencodepresetdialog.h \
#    dialogs/alignaudiodialog.h \
#    dialogs/alignmentarray.h \
#    dialogs/bitratedialog.h \
#    dialogs/customprofiledialog.h \
#    dialogs/durationdialog.h \
#    dialogs/editmarkerdialog.h \
#    dialogs/filedatedialog.h \
#    dialogs/listselectiondialog.h \
#    dialogs/longuitask.h \
#    dialogs/multifileexportdialog.h \
#    dialogs/resourcedialog.h \
#    dialogs/saveimagedialog.h \
#    dialogs/slideshowgeneratordialog.h \
#    dialogs/systemsyncdialog.h \
#    dialogs/textviewerdialog.h \
#    dialogs/transcodedialog.h \
#    dialogs/unlinkedfilesdialog.h \
#    docks/encodedock.h \
#    docks/filtersdock.h \
#    docks/jobsdock.h \
#    docks/keyframesdock.h \
#    docks/markersdock.h \
#    docks/notesdock.h \
#    docks/playlistdock.h \
#    docks/recentdock.h \
#    docks/scopedock.h \
#    docks/timelinedock.h \
#    jobqueue.h \
#    jobs/abstractjob.h \
#    jobs/bitrateviewerjob.h \
#    jobs/encodejob.h \
#    jobs/ffmpegjob.h \
#    jobs/ffprobejob.h \
#    jobs/gopro2gpxjob.h \
#    jobs/meltjob.h \
#    jobs/postjobaction.h \
#    jobs/qimagejob.h \
#    jobs/videoqualityjob.h \
#    mainwindow.h \
#    mltcontroller.h \
#    mltxmlchecker.h \
#    models/actionsmodel.h \
#    models/alignclipsmodel.h \
#    models/attachedfiltersmodel.h \
#    models/audiolevelstask.h \
#    models/keyframesmodel.h \
#    models/markersmodel.h \
#    models/metadatamodel.h \
#    models/motiontrackermodel.h \
#    models/multitrackmodel.h \
#    models/playlistmodel.h \
#    models/resourcemodel.h \
#    openotherdialog.h \
#    player.h \
#    playslider.h \
#    proxymanager.h \
#    qmltypes/colordialog.h \
#    qmltypes/colorpickeritem.h \
#    qmltypes/colorwheelitem.h \
#    qmltypes/filedialog.h \
#    qmltypes/fontdialog.h \
#    qmltypes/messagedialog.h \
#    qmltypes/qmlapplication.h \
#    qmltypes/qmleditmenu.h \
#    qmltypes/qmlfile.h \
#    qmltypes/qmlfilter.h \
#    qmltypes/qmlmarkermenu.h \
#    qmltypes/qmlmetadata.h \
#    qmltypes/qmlproducer.h \
#    qmltypes/qmlprofile.h \
#    qmltypes/qmlrichtext.h \
#    qmltypes/qmlrichtextmenu.h \
#    qmltypes/qmlutilities.h \
#    qmltypes/qmlview.h \
#    qmltypes/thumbnailprovider.h \
#    qmltypes/timelineitems.h \
#    scrubbar.h \
#    settings.h \
#    sharedframe.h \
##    shotcut_autogen/include/ui_addencodepresetdialog.h \
##    shotcut_autogen/include/ui_alsawidget.h \
##    shotcut_autogen/include/ui_avformatproducerwidget.h \
##    shotcut_autogen/include/ui_avfoundationproducerwidget.h \
##    shotcut_autogen/include/ui_blipproducerwidget.h \
##    shotcut_autogen/include/ui_colorbarswidget.h \
##    shotcut_autogen/include/ui_colorproducerwidget.h \
##    shotcut_autogen/include/ui_countproducerwidget.h \
##    shotcut_autogen/include/ui_customprofiledialog.h \
##    shotcut_autogen/include/ui_decklinkproducerwidget.h \
##    shotcut_autogen/include/ui_directshowvideowidget.h \
##    shotcut_autogen/include/ui_durationdialog.h \
##    shotcut_autogen/include/ui_encodedock.h \
##    shotcut_autogen/include/ui_gdigrabwidget.h \
##    shotcut_autogen/include/ui_glaxnimateproducerwidget.h \
##    shotcut_autogen/include/ui_imageproducerwidget.h \
##    shotcut_autogen/include/ui_isingwidget.h \
##    shotcut_autogen/include/ui_jackproducerwidget.h \
##    shotcut_autogen/include/ui_jobsdock.h \
##    shotcut_autogen/include/ui_lissajouswidget.h \
##    shotcut_autogen/include/ui_listselectiondialog.h \
##    shotcut_autogen/include/ui_lumamixtransition.h \
##    shotcut_autogen/include/ui_mainwindow.h \
##    shotcut_autogen/include/ui_networkproducerwidget.h \
##    shotcut_autogen/include/ui_newprojectfolder.h \
##    shotcut_autogen/include/ui_noisewidget.h \
##    shotcut_autogen/include/ui_openotherdialog.h \
##    shotcut_autogen/include/ui_plasmawidget.h \
##    shotcut_autogen/include/ui_playlistdock.h \
##    shotcut_autogen/include/ui_pulseaudiowidget.h \
##    shotcut_autogen/include/ui_recentdock.h \
##    shotcut_autogen/include/ui_servicepresetwidget.h \
##    shotcut_autogen/include/ui_systemsyncdialog.h \
##    shotcut_autogen/include/ui_textproducerwidget.h \
##    shotcut_autogen/include/ui_textviewerdialog.h \
##    shotcut_autogen/include/ui_timelinepropertieswidget.h \
##    shotcut_autogen/include/ui_toneproducerwidget.h \
##    shotcut_autogen/include/ui_trackpropertieswidget.h \
##    shotcut_autogen/include/ui_transcodedialog.h \
##    shotcut_autogen/include/ui_unlinkedfilesdialog.h \
##    shotcut_autogen/include/ui_video4linuxwidget.h \
##    shotcut_autogen/include/ui_x11grabwidget.h \
#    shotcut_autogen/moc_predefs.h \
#    shotcut_mlt_properties.h \
#    spatialmedia/box.h \
#    spatialmedia/constants.h \
#    spatialmedia/container.h \
#    spatialmedia/mpeg4_container.h \
#    spatialmedia/sa3d.h \
#    spatialmedia/spatialmedia.h \
#    track.h \
#    transcoder.h \
#    transportcontrol.h \
#    ui_mainwindow.h \
#    util.h \
#    videowidget.h \
#    widgets/alsawidget.h \
#    widgets/audiometerwidget.h \
#    widgets/audioscale.h \
#    widgets/avformatproducerwidget.h \
#    widgets/avfoundationproducerwidget.h \
#    widgets/blipproducerwidget.h \
#    widgets/colorbarswidget.h \
#    widgets/colorproducerwidget.h \
#    widgets/colorwheel.h \
#    widgets/countproducerwidget.h \
#    widgets/d3dvideowidget.h \
#    widgets/decklinkproducerwidget.h \
#    widgets/directshowvideowidget.h \
#    widgets/docktoolbar.h \
#    widgets/editmarkerwidget.h \
#    widgets/exportpresetstreeview.h \
#    widgets/fixx11h.h \
#    widgets/frameratewidget.h \
#    widgets/gdigrabwidget.h \
#    widgets/glaxnimateproducerwidget.h \
#    widgets/iecscale.h \
#    widgets/imageproducerwidget.h \
#    widgets/isingwidget.h \
#    widgets/jackproducerwidget.h \
#    widgets/lineeditclear.h \
#    widgets/lissajouswidget.h \
#    widgets/lumamixtransition.h \
#    widgets/networkproducerwidget.h \
#    widgets/newprojectfolder.h \
#    widgets/noisewidget.h \
#    widgets/openglvideowidget.h \
#    widgets/plasmawidget.h \
#    widgets/playlisticonview.h \
#    widgets/playlistlistview.h \
#    widgets/playlisttable.h \
#    widgets/producerpreviewwidget.h \
#    widgets/pulseaudiowidget.h \
#    widgets/resourcewidget.h \
#    widgets/scopes/audioloudnessscopewidget.h \
#    widgets/scopes/audiopeakmeterscopewidget.h \
#    widgets/scopes/audiospectrumscopewidget.h \
#    widgets/scopes/audiowaveformscopewidget.h \
#    widgets/scopes/scopewidget.h \
#    widgets/scopes/videohistogramscopewidget.h \
#    widgets/scopes/videorgbparadescopewidget.h \
#    widgets/scopes/videorgbwaveformscopewidget.h \
#    widgets/scopes/videovectorscopewidget.h \
#    widgets/scopes/videowaveformscopewidget.h \
#    widgets/scopes/videozoomscopewidget.h \
#    widgets/scopes/videozoomwidget.h \
#    widgets/screenselector.h \
#    widgets/servicepresetwidget.h \
#    widgets/slideshowgeneratorwidget.h \
#    widgets/statuslabelwidget.h \
#    widgets/textproducerwidget.h \
#    widgets/timelinepropertieswidget.h \
#    widgets/timespinbox.h \
#    widgets/toneproducerwidget.h \
#    widgets/trackpropertieswidget.h \
#    widgets/video4linuxwidget.h \
#    widgets/x11grabwidget.h

#FORMS += \
#    clipmain.ui \
#    dialogs/addencodepresetdialog.ui \
#    dialogs/customprofiledialog.ui \
#    dialogs/durationdialog.ui \
#    dialogs/listselectiondialog.ui \
#    dialogs/systemsyncdialog.ui \
#    dialogs/textviewerdialog.ui \
#    dialogs/transcodedialog.ui \
#    dialogs/unlinkedfilesdialog.ui \
#    docks/encodedock.ui \
#    docks/jobsdock.ui \
#    docks/playlistdock.ui \
#    docks/recentdock.ui \
#    openotherdialog.ui \
#    widgets/alsawidget.ui \
#    widgets/avformatproducerwidget.ui \
#    widgets/avfoundationproducerwidget.ui \
#    widgets/blipproducerwidget.ui \
#    widgets/colorbarswidget.ui \
#    widgets/colorproducerwidget.ui \
#    widgets/countproducerwidget.ui \
#    widgets/decklinkproducerwidget.ui \
#    widgets/directshowvideowidget.ui \
#    widgets/gdigrabwidget.ui \
#    widgets/glaxnimateproducerwidget.ui \
#    widgets/imageproducerwidget.ui \
#    widgets/isingwidget.ui \
#    widgets/jackproducerwidget.ui \
#    widgets/lissajouswidget.ui \
#    widgets/lumamixtransition.ui \
#    widgets/networkproducerwidget.ui \
#    widgets/newprojectfolder.ui \
#    widgets/noisewidget.ui \
#    widgets/plasmawidget.ui \
#    widgets/pulseaudiowidget.ui \
#    widgets/servicepresetwidget.ui \
#    widgets/textproducerwidget.ui \
#    widgets/timelinepropertieswidget.ui \
#    widgets/toneproducerwidget.ui \
#    widgets/trackpropertieswidget.ui \
#    widgets/video4linuxwidget.ui \
#    widgets/x11grabwidget.ui
HEADERS += \
    clipmain.h \
    ffmpeg_util/extractduration.h \
    ffmpeg_util/extractthumbnail.h \
    graphics/graphicscommon.h \
    graphics/graphicsscene.h \
    graphics/graphicsviewscalable.h \
    graphics/graphicswidgetcomposition.h \
    graphics/graphicswidgetresources.h \
    graphics/graphicswidgetsegment.h \
    graphics/graphicswidgetsequence.h \
    graphics/graphicswidgettimeline.h \
    graphics/videoitem.h \
    imf/imfcommon.h \
    imf/imfpackage.h \
    playslider.h \
    track.h \
    utils/FrameRateManager.h \
    utils/commands.h \
    videoplaywidget.h \
#    widget/widgetcomposition.h \
    widget/widgettrackdetails.h

SOURCES += \
    clipmain.cpp \
    ffmpeg_util/extractduration.cpp \
    ffmpeg_util/extractthumbnail.cpp \
    graphics/graphicscommon.cpp \
    graphics/graphicsscene.cpp \
    graphics/graphicsscenebase.cpp \
    graphics/graphicsviewscalable.cpp \
    graphics/graphicswidgetcomposition.cpp \
    graphics/graphicswidgetresources.cpp \
    graphics/graphicswidgetsegment.cpp \
    graphics/graphicswidgetsequence.cpp \
    graphics/graphicswidgettimeline.cpp \
    graphics/videoitem.cpp \
    imf/imfcommon.cpp \
    imf/imfpackage.cpp \
    playslider.cpp \
    track.cpp \
    main.cpp \
    utils/FrameRateManager.cpp \
    utils/commands.cpp \
    videoplaywidget.cpp \
#    widget/widgetcomposition.cpp \
    widget/widgettrackdetails.cpp

FORMS += \
    clipmain.ui

TRANSLATIONS += \
    Clip_zh_CN.ts
#CONFIG += lrelease
CONFIG += debug
CONFIG += embed_translations

#QMAKE_CXXFLAGS_DEBUG += -O0
#QMAKE_CFLAGS_DEBUG += -O0

LIBS_TYPE = msvc

contains(QT_ARCH, x86_64) {

    message("64-bit")

    message($$LIBS_TYPE)

    contains(LIBS_TYPE, msvc) {
        QMAKE_CFLAGS += /utf-8
        INCLUDEPATH += $$PWD/build64/ffmpeg-n4.4.1-msvc/include
        LIBS += $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/avcodec.lib \
            $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/avdevice.lib \
            $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/avfilter.lib \
            $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/avformat.lib \
            $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/avutil.lib \
            $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/postproc.lib \
            $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/swresample.lib \
            $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/swscale.lib
        lib_install.files += $$PWD/build64/ffmpeg-n4.4.1-msvc/bin/*.dll
        CONFIG(debug, debug|release){
           lib_install.path = $${OUT_PWD}/Debug
        }
        CONFIG(release, debug|release){
           lib_install.path = $${OUT_PWD}/Release
        }
        other_install.files += $$PWD/juren-30s.mp4
        other_install.path += $${OUT_PWD}
        INSTALLS += lib_install other_install
    }

    contains(LIBS_TYPE, msvc-static) {
    INCLUDEPATH += $$PWD/build64/ffmepg-4.4-msvc/include
    LIBS += $$PWD/build64/ffmepg-4.4-msvc/lib/libavcodec.a mfplat.lib mfuuid.lib ole32.lib strmiids.lib ole32.lib user32.lib \
        $$PWD/build64/ffmepg-4.4-msvc/lib/libavdevice.a psapi.lib ole32.lib strmiids.lib uuid.lib oleaut32.lib shlwapi.lib gdi32.lib vfw32.lib \
        $$PWD/build64/ffmepg-4.4-msvc/lib/libavfilter.a \
        $$PWD/build64/ffmepg-4.4-msvc/lib/libavformat.a secur32.lib ws2_32.lib \
        $$PWD/build64/ffmepg-4.4-msvc/lib/libavutil.a user32.lib bcrypt.lib \
        $$PWD/build64/ffmepg-4.4-msvc/lib/libpostproc.a \
        $$PWD/build64/ffmepg-4.4-msvc/lib/libswresample.a \
        $$PWD/build64/ffmepg-4.4-msvc/lib/libswscale.a
    }

    contains(LIBS_TYPE, mingw) {
        QMAKE_CFLAGS += /utf-8
        INCLUDEPATH += $$PWD/build64/ffmpeg-v6.0-mingw/include \
            $$PWD/build64/mlt-ffmpeg6.0/include/mlt-7
#            $$PWD/build64/CuteLogger/include \
#            $$PWD/build64/fftw3/include
        LIBS += $$PWD/build64/ffmpeg-v6.0-mingw/bin/avcodec.lib \
            $$PWD/build64/ffmpeg-v6.0-mingw/bin/avdevice.lib \
            $$PWD/build64/ffmpeg-v6.0-mingw/bin/avfilter.lib \
            $$PWD/build64/ffmpeg-v6.0-mingw/bin/avformat.lib \
            $$PWD/build64/ffmpeg-v6.0-mingw/bin/avutil.lib \
            $$PWD/build64/ffmpeg-v6.0-mingw/bin/postproc.lib \
            $$PWD/build64/ffmpeg-v6.0-mingw/bin/swresample.lib \
            $$PWD/build64/ffmpeg-v6.0-mingw/bin/swscale.lib \
            $$PWD/build64/mlt-ffmpeg6.0/lib/libmlt++-7.dll.a
#            $$PWD/build64/CuteLogger/libCuteLogger.dll.a \
#            $$PWD/build64/fftw3/lib/libfftw3.dll.a
        lib_install.files += $$PWD/build64/ffmpeg-v6.0-mingw/bin/*.dll \
            $$PWD/build64/mlt-ffmpeg6.0/lib/libmlt++.dll
#            $$PWD/build64/CuteLogger/libCuteLogger.dll \
#            $$PWD/build64/fftw3/bin/libfftw3-3.dll
        CONFIG(debug, debug|release){
           lib_install.path = $${OUT_PWD}/Debug
        }
        CONFIG(release, debug|release){
           lib_install.path = $${OUT_PWD}/Release
        }
        other_install.path += $${OUT_PWD}
        INSTALLS += lib_install other_install
    }

}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
#    Shotcut/Controls/Button.qml \
#    Shotcut/Controls/ColorPicker.qml \
#    Shotcut/Controls/ComboBox.qml \
#    Shotcut/Controls/DoubleSpinBox.qml \
#    Shotcut/Controls/EditMenu.qml \
#    Shotcut/Controls/Gauge.qml \
#    Shotcut/Controls/GradientControl.qml \
#    Shotcut/Controls/HorizontalScrollBar.qml \
#    Shotcut/Controls/HoverTip.qml \
#    Shotcut/Controls/KeyframableFilter.qml \
#    Shotcut/Controls/KeyframesButton.qml \
#    Shotcut/Controls/Marker.qml \
#    Shotcut/Controls/MarkerBar.qml \
#    Shotcut/Controls/MotionTrackerDialog.qml \
#    Shotcut/Controls/Preset.qml \
#    Shotcut/Controls/RectangleControl.qml \
#    Shotcut/Controls/SaveDefaultButton.qml \
#    Shotcut/Controls/SimplePropertyUI.qml \
#    Shotcut/Controls/SliderSpinner.qml \
#    Shotcut/Controls/TextFilterUi.qml \
#    Shotcut/Controls/TextFilterVui.qml \
#    Shotcut/Controls/TimeSpinner.qml \
#    Shotcut/Controls/TipBox.qml \
#    Shotcut/Controls/ToggleButton.qml \
#    Shotcut/Controls/ToolButton.qml \
#    Shotcut/Controls/UndoButton.qml \
#    Shotcut/Controls/VerticalScrollBar.qml \
#    Shotcut/Controls/VuiBase.qml \
#    Shotcut/Controls/qmldir \
#    shotcut_autogen/2JHE5F47XL/moc_audioloudnessscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_audiopeakmeterscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_audiospectrumscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_audiowaveformscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_scopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_videohistogramscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_videorgbparadescopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_videorgbwaveformscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_videovectorscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_videowaveformscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_videozoomscopewidget.cpp.d \
#    shotcut_autogen/2JHE5F47XL/moc_videozoomwidget.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_actionsdialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_addencodepresetdialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_alignaudiodialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_bitratedialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_customprofiledialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_durationdialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_editmarkerdialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_filedatedialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_listselectiondialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_multifileexportdialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_resourcedialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_saveimagedialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_slideshowgeneratordialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_systemsyncdialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_textviewerdialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_transcodedialog.cpp.d \
#    shotcut_autogen/2NRMJ5X7RK/moc_unlinkedfilesdialog.cpp.d \
#    shotcut_autogen/7CL2LH2DRO/moc_filtercontroller.cpp.d \
#    shotcut_autogen/7CL2LH2DRO/moc_scopecontroller.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_abstractjob.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_bitrateviewerjob.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_encodejob.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_ffmpegjob.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_ffprobejob.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_gopro2gpxjob.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_meltjob.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_qimagejob.cpp.d \
#    shotcut_autogen/AJN4HOEG3V/moc_videoqualityjob.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_actions.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_autosavefile.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_database.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_jobqueue.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_mainwindow.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_mltcontroller.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_openotherdialog.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_player.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_scrubbar.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_settings.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_transcoder.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_transportcontrol.cpp.d \
#    shotcut_autogen/EWIEGA46WW/moc_videowidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_alsawidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_audiometerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_audioscale.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_avformatproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_avfoundationproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_blipproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_colorbarswidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_colorproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_colorwheel.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_countproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_d3dvideowidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_decklinkproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_directshowvideowidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_docktoolbar.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_editmarkerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_frameratewidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_gdigrabwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_glaxnimateproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_imageproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_isingwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_jackproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_lineeditclear.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_lissajouswidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_lumamixtransition.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_networkproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_newprojectfolder.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_noisewidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_openglvideowidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_plasmawidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_playlisticonview.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_playlistlistview.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_playlisttable.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_producerpreviewwidget.cpp.d \
#    shotcut_autogen/IMAN3f6LHMA/moc_pulseaudiowidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_resourcewidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_screenselector.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_servicepresetwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_slideshowgeneratorwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_statuslabelwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_textproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_timelinepropertieswidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_timespinbox.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_toneproducerwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_trackpropertieswidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_video4linuxwidget.cpp.d \
#    shotcut_autogen/IMAN36LHMA/moc_x11grabwidget.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_actionsmodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_alignclipsmodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_attachedfiltersmodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_keyframesmodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_markersmodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_metadatamodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_motiontrackermodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_multitrackmodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_playlistmodel.cpp.d \
#    shotcut_autogen/IVK4DJNV27/moc_resourcemodel.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_colordialog.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_colorpickeritem.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_colorwheelitem.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_filedialog.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_fontdialog.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_messagedialog.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlapplication.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmleditmenu.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlfile.cpp.d \
#    s
#    hotcut_autogen/OJWBM6OTSN/moc_qmlfilter.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlmarkermenu.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlmetadata.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlproducer.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlprofile.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlrichtext.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlrichtextmenu.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlutilities.cpp.d \
#    shotcut_autogen/OJWBM6OTSN/moc_qmlview.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_encodedock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_filtersdock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_jobsdock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_keyframesdock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_markersdock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_notesdock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_playlistdock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_recentdock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_scopedock.cpp.d \
#    shotcut_autogen/SVAOMNV2MZ/moc_timelinedock.cpp.d \
#    shotcut_autogen/deps \
#    shotcut_autogen/include/actionsdialog.moc \
#    shotcut_autogen/include/actionsdialog.moc.d \
#    shotcut_autogen/include/alignaudiodialog.moc \
#    shotcut_autogen/include/alignaudiodialog.moc.d \
#    shotcut_autogen/include/markersdock.moc \
#    shotcut_autogen/include/markersdock.moc.d \
#    shotcut_autogen/include/moc_timelinecommands.cpp.d \
#    shotcut_autogen/include/playlistdock.moc \
#    shotcut_autogen/include/playlistdock.moc.d \
#    shotcut_autogen/include/timelineitems.moc \
#    shotcut_autogen/include/timelineitems.moc.d \
#    shotcut_autogen/timestamp \
    graphics/ReadMe.txt \
    resources/branch_open.png \
    resources/branch_open_disabled.png \
    resources/cursor_crop_left.png \
    resources/cursor_crop_right.png \
    resources/down_arrow.png \
    resources/down_arrow_disabled.png \
    resources/down_arrow_hover.png \
    resources/film.png \
    resources/frame_blank.png \
    resources/frame_error.png \
    resources/pause.png \
    resources/play.png \
    resources/scroll_down.png \
    resources/scroll_down_disabled.png \
    resources/scroll_down_hover.png \
    resources/scroll_left.png \
    resources/scroll_left_disabled.png \
    resources/scroll_left_hover.png \
    resources/scroll_right.png \
    resources/scroll_right_disabled.png \
    resources/scroll_right_hover.png \
    resources/scroll_up.png \
    resources/scroll_up_disabled.png \
    resources/scroll_up_hover.png \
    resources/sound.png \
    resources/sound_bw.png \
    resources/sound_small.png \
    resources/stop.png \
    resources/stylesheet.qss \
    resources/text.png \
    resources/text_bw.png \
    resources/text_small.png \
    resources/up_arrow.png \
    resources/up_arrow_disabled.png \
    resources/up_arrow_hover.png \
#    test.qml \
#    timeline.js \
#    timeline.qml

RESOURCES += \
    qml.qrc \
    resources/resource.qrc
