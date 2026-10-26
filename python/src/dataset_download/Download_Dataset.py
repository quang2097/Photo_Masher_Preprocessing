from roboflow import Roboflow
rf = Roboflow(api_key="6tvItSa68XyI1vLXlvnG")
project = rf.workspace("tran-quang").project("corn-leaf-disease-hgosu-pu0yr")
version = project.version(1)
dataset = version.download("yolo26")