file = [deg_plaI185lacI153_4.xml]

MoDeL
{
	reaction id = [deg_plaI185lacI153_4], name = [plaI185lacI153_4 degradation reaction], reversible = [false], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[degradation of complex plaI185lacI153_4];
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
				speciesReference:[plaI185lacI153_4];
				speciesLabel:[plaI185lacI153_4];
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
						ci:[plaI185lacI153_4];
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