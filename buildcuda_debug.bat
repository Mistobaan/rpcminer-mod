"%CUDA_PATH%bin\nvcc.exe" ^
	-Xcompiler "/EHsc /W3 /nologo /Od /Zi /MTd" ^
	-gencode arch=compute_13,code=\"sm_13\" ^
	-gencode arch=compute_20,code=\"sm_20\" ^
	-gencode arch=compute_30,code=\"sm_30\" ^
	-gencode arch=compute_35,code=\"sm_35\" ^
	-gencode arch=compute_35,code=\"compute_35\" ^
	-Xptxas=-v ^
	--compile ^
	-m32 ^
	-O0 ^
	-D_BITCOIN_MINER_CUDA_ ^
	-D_WIN32 ^
	-D_DEBUG ^
	-DNVCC ^
	-I "%CUDA_PATH%include" ^
	-I "src\cuda" ^
	-o "src\cuda\bitcoinminercuda.cu.obj" ^
	"src\cuda\bitcoinminercuda.cu"
