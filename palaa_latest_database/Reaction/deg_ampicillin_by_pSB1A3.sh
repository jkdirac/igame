file = [deg_ampicillin_by_pSB1A3.xml]

MoDeL
{
	reaction id = [deg_ampicillin_by_pSB1A3], name = [pSB1A3-induced ampicillin degradation], reversible = [false], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[pSB1A3-induced degradation of ampicillin];
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
				speciesReference:[ampicillin_compound];
				speciesLabel:[ampicillin_compound];
				compartmentLabel:[E_coli] itself = [];
			}
		}
		listOfModifiers
		{
			modifier
			{
				speciesReference:[tm_pSB1A3];
				speciesLabel:[tm_pSB1A3];
				compartmentLabel:[E_coli] itself = [];
			}
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
				math:[kdeg*pSB1A3*ampicillin_compound*E_coli];
				listOfLocalParameters
				{
					localParameter
					{
						id:[kdeg];
						name:[pSB1A3-induced degradation rate of ampicillin];
						value:[1000000000];
						units:[litre_per_mole_per_second];
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
