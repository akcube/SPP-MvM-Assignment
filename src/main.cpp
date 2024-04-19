#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <fstream>
#include <memory>
#include <cstdint>
#include <filesystem>
#include <string>

namespace solution{
	std::string compute(const std::string &m1_path, const std::string &m2_path, int n, int k, int m){
		std::string sol_path = std::filesystem::temp_directory_path() / "student_sol.dat";
		std::ofstream sol_fs(sol_path, std::ios::binary);
		std::ifstream m1_fs(m1_path, std::ios::binary), m2_fs(m2_path, std::ios::binary);
		const auto m1 = std::make_unique<float[]>(n*k), m2 = std::make_unique<float[]>(k*m);
		m1_fs.read(reinterpret_cast<char*>(m1.get()), sizeof(float) * n * k);
		m2_fs.read(reinterpret_cast<char*>(m2.get()), sizeof(float) * k * m);
		m1_fs.close(); m2_fs.close();
		auto result = std::make_unique<float[]>(n*m);
	    for (int i = 0; i < n; i++)
	        for (int j = 0; j < m; j++) {
	            result[i*m + j] = 0;
	            for (int l = 0; l < k; ++l) 
	            	result[i*m + j] += m1[i*k + l] * m2[l*m + j];
	        }
		sol_fs.write(reinterpret_cast<const char*>(result.get()), sizeof(float) * n * m);
		sol_fs.close();
		return sol_path;
	}
};
