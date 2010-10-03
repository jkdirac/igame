file = [deg_IPTG.xml]

MoDeL
{
	reaction id = [deg_IPTG], name = [IPTG degradation reaction], reversible = [false], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[regular degradation of IPTG_compound];
		}
		listOfCompartments
		{
			compartment
			{
				compartmentReference:[Flask];
				currentCompartmentLabel:[Flask];
				parentCompartmentLabel:[ROOT];
			}
			compartment
			{
				compartmentReference:[E_coli];
				currentCompartmentLabel:[E_coli];
				parentCompartmentLabel:[Flask];
			}
		}
		listOfReactants
		{
			reactant	
			{
				speciesReference:[IPTG_compound];
				speciesLabel:[IPTG_compound];
				compartmentLabel:[E_coli] itself = [];
			}
		}
		listOfModifiers
		{
		}
		listOfProducts
		{
		}
		listOfSubstituentTransfers
		{
		}
		kineticLaw
		{
			forwardKineticlaw
			{
				math
				{
					apply
					{
						times
						{
						}
						ci:[kdeg];
						ci:[IPTG_compound];
						ci:[E_coli];
					}
				}
				listOfLocalParameters
				{
					localParameter
					{
						id:[kdeg];
						name:[degradation rate];
						value:[0.01];
						units:[per_second];
						constant:[true];
					}
				}
				listOfReferencedParameters
				{
				}
				listOfConstraints
				{
				}
			}
			reverseKineticLaw
			{
			}
		}
	}
}

