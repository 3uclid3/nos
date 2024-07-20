extern "C" void _start()
{
    while (true)
        asm volatile ("cli; hlt");
}
