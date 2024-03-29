#pragma once

namespace Schmog {


	enum class ShaderDataType 
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		UInt,
		UByte, UByte4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:			return 4;
			case ShaderDataType::Float2:		return 4*2;
			case ShaderDataType::Float3:		return 4*3;
			case ShaderDataType::Float4:		return 4*4;

			case ShaderDataType::Mat3:			return 4*3*3;
			case ShaderDataType::Mat4:			return 4*4*4;

			case ShaderDataType::Int:			return 4;
			case ShaderDataType::Int2:			return 4 * 2;
			case ShaderDataType::Int3:			return 4 * 3;
			case ShaderDataType::Int4:			return 4 * 4;

			case ShaderDataType::UInt:			return 4;

			case ShaderDataType::UByte:			return 1;
			case ShaderDataType::UByte4:		return 4;

			case ShaderDataType::Bool:			return 1;
		}

		SG_CORE_ASSERT(false, "Unknown Shader Data Type");
		return 0;
	}

	struct BufferLayoutEntry
	{
		ShaderDataType type;
		std::string name;
		uint32_t size;
		size_t offset;
		bool normalized;

		BufferLayoutEntry() = default;

		BufferLayoutEntry(ShaderDataType type, const std::string& name, bool normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
		{

		}

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3 * 3;
				case ShaderDataType::Mat4:    return 4 * 4;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
				case ShaderDataType::UInt:    return 1;
				case ShaderDataType::UByte:    return 1;
				case ShaderDataType::UByte4:    return 4;
			}

			SG_CORE_ASSERT(false, "Unknown shader data type");
			return 0;
		}
	};

	class BufferLayout
	{
	public:

		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferLayoutEntry>& init)
			: m_Elements(init) 
		{
			CalculateOffsetAndStride();
		}

		std::vector<BufferLayoutEntry> GetElements() const { return m_Elements; }
		uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferLayoutEntry>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferLayoutEntry>::iterator end() { return m_Elements.end(); }

		std::vector<BufferLayoutEntry>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferLayoutEntry>::const_iterator end() const { return m_Elements.end(); }

	private:

		void CalculateOffsetAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.offset = offset;
				offset += element.size;
				m_Stride += element.size;
			}
		}

	private:
		std::vector<BufferLayoutEntry> m_Elements;
		uint32_t m_Stride = 0;
	};


	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
		static std::shared_ptr<VertexBuffer> Create(uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;


		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

}