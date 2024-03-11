cargo build --release --target x86_64-unknown-linux-gnu
gcc -ffunction-sections -fdata-sections -DPC_TEST src/main.c target/x86_64-unknown-linux-gnu/release/libarmv8m_test.a -o target/myapp

target/myapp
