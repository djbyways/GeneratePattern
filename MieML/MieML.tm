:Begin:
:Function:       AmplitudeCoefficients
:Pattern:     	AmplitudeCoefficients[x_?NumericQ, m_?NumericQ, Theta_?NumericQ]
:Arguments:      {Re@x, Im@x, Re@m, Im@m, {Theta}}
:ArgumentTypes:  {Real, Real, Real, Real, RealList}
:ReturnType:     Manual
:End:

:Begin:
:Function:       AmplitudeCoefficients
:Pattern:     	AmplitudeCoefficients[x_?NumericQ, m_?NumericQ, Theta_?(VectorQ[#,NumericQ]&)]
:Arguments:      {Re@x, Im@x, Re@m, Im@m, Theta}
:ArgumentTypes:  {Real, Real, Real, Real, RealList}
:ReturnType:     Manual
:End:

:Begin:
:Function:       ScatteringCoefficients
:Pattern:     	ScatteringCoefficients[x_?NumericQ, m_?NumericQ, Nmax_Integer]
:Arguments:      {Re@x, Im@x, Re@m, Im@m, Nmax}
:ArgumentTypes:  {Real, Real, Real, Real, Integer}
:ReturnType:     Manual
:End:

:Begin:
:Function:       AngleFunctions
:Pattern:     	AngleFunctions[Theta_Real, Nmax_Integer]
:Arguments:      {Theta, Nmax}
:ArgumentTypes:  {Real, Integer}
:ReturnType:     Manual
:End:

