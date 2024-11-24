/******************************************************************************
 * Project:  libspatialindex - A C++ library for spatial indexing
 * Author:   Marios Hadjieleftheriou, mhadji@gmail.com
 ******************************************************************************
 * Copyright (c) 2002, Marios Hadjieleftheriou
 *
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
******************************************************************************/

#pragma once

#include <cstring>

namespace SpatialIndex
{
	namespace StorageManager
	{
		class MemoryStorageManager : public SpatialIndex::IStorageManager
		{
		public:
			MemoryStorageManager(Tools::PropertySet&);

			~MemoryStorageManager() override;

			void flush() override;
			void loadByteArray(const id_type page, uint32_t& len, uint8_t** data) override;
			void storeByteArray(id_type& page, const uint32_t len, const uint8_t* const data) override;

			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			void loadByteArray_nomalloc(const id_type page, uint8_t* data) override {
				throw std::runtime_error("Not Implemented...");
			}
			void loadByteArray_nomalloc_cstyle(const id_type page, uint8_t* data) override {
				throw std::runtime_error("Not Implemented...");
			}
			uint32_t loadByteArrayLength(const id_type page) override {
				throw std::runtime_error("Not Implemented...");
			}
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			void deleteByteArray(const id_type page) override;

		private:
			class Entry
			{
			public:
				uint8_t* m_pData;
				uint32_t m_length;

				Entry(uint32_t l, const uint8_t* const d) : m_pData(nullptr), m_length(l)
				{
					m_pData = new uint8_t[m_length];
					memcpy(m_pData, d, m_length);
				}

				~Entry() { 
					// delete[] m_pData; 
				}
			}; // Entry

			std::vector<Entry*> m_buffer;
			std::stack<id_type> m_emptyPages;
		}; // MemoryStorageManager
	}
}
