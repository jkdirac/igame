file = [deg_tm_pSB1A3.xml]

MoDeL
{
	reaction id = [deg_tm_pSB1A3], name = [plasmid tm_pSB1A3 degradation reaction], reversible = [false], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[regular degradation of plasmid with backbone tm_pSB1A3];
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
				speciesReference:[tm_pSB1A3];
				speciesLabel:[tm_pSB1A3];
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
						ci:[tm_pSB1A3];
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
