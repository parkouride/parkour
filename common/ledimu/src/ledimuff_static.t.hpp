#ifdef IN_LEDIMUFILECLASS

#ifndef ARDUINO

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

	return static_cast<int>(retval);
}

#else // ARDUINO

static int RequiredPixelCountFor(const char* filename)
{
    return 8; // TODO: Implement for arduino
}

#endif // ARDUINO

#endif // IN_LEDIMUFILECLASS
