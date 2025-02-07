#pragma once

#include <string>
#include "SGLdecl.hpp"


#include "Component.hpp"
#include "ShaderData.hpp"
#include "ShaderProgram.hpp"


namespace sgl
{
	class Shader : public ShaderProgram, public Component
	{
	public:
		using Component::transform;
		Shader(const std::string &path_to_vertex_shader, const std::string &path_to_fragment_shader);
		void draw() const override;
	};

} // namespace sgl
