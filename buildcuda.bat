"%CUDA_PATH%bin\nvcc.exe" ^
	-Xcompiler "/EHsc /W3 /nologo /O2 /Zi /MD" ^
	-gencode arch=compute_13,code=\"sm_13\" ^
	-gencode arch=compute_20,code=\"sm_20\" ^
	-gencode arch=compute_30,code=\"sm_30\" ^
	-gencode arch=compute_35,code=\"sm_35\" ^
	-gencode arch=compute_35,code=\"compute_35\" ^
	-Xptxas=-v ^
	--compile ^
	-m64 ^
	-O3 ^
	-D_BITCOIN_MINER_CUDA_ ^
	-D_WIN32 ^
	-D_WIN64 ^
	-DNVCC ^
	-I "%CUDA_PATH%include" ^
	-I "src\cuda" ^
	-o "src\cuda\bitcoinminercuda.cu.obj" ^
	"src\cuda\bitcoinminercuda.cu"
