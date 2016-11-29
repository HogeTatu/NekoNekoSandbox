@echo off

pushd Content

for /f "usebackq" %%d in (`"dir /ad/b/s | sort /R"`) do rd "%%d"

popd
