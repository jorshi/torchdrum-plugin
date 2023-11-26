import cppyy

cppyy.include("source/TorchDrumLib.h")
cppyy.load_library("build/libTorchDrumLib")

OnsetDetection = cppyy.gbl.OnsetDetection

def test_onset_detection_init():
    onset_detection = OnsetDetection()
    onset_detection.prepare(44100)
