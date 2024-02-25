#pragma once


namespace Tiler {

	class RenderContext {
	public:
		RenderContext() = default;
		virtual ~RenderContext() = default;

		virtual void Initialize() = 0;
		virtual void SwapBuffers() = 0;
	};

}