#ifdef IN_LEDIMUFILECLASS

static int RequiredPixelCountFor(const char* filename)
{
	std::ifstream datafile{filename};
	if (!datafile)
	{
		return -1;
	}

	datafile.seekg(5); // Skip PARK and State count
	uint8_t retval;
	datafile.read(reinterpret_cast<char *>(&retval), 1);
	std::cout << static_cast<int>(retval) << std::endl;

	return static_cast<int>(retval);
}

#endif // IN_LEDIMUFILECLASS