classdef SpatialForceVectorSemanticsBase < SwigRef
  methods
    function this = swig_this(self)
      this = iDynTreeMEX(3, self);
    end
    function self = SpatialForceVectorSemanticsBase(varargin)
      if nargin==1 && strcmp(class(varargin{1}),'SwigRef')
        if ~isnull(varargin{1})
          self.swigPtr = varargin{1}.swigPtr;
        end
      else
        tmp = iDynTreeMEX(533, varargin{:});
        self.swigPtr = tmp.swigPtr;
        tmp.SwigClear();
      end
    end
    function varargout = check_linear2angularConsistency(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(534, self, varargin{:});
    end
    function varargout = toString(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(535, self, varargin{:});
    end
    function varargout = display(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(536, self, varargin{:});
    end
    function delete(self)
      if self.swigPtr
        iDynTreeMEX(537, self);
        self.SwigClear();
      end
    end
  end
  methods(Static)
  end
end
