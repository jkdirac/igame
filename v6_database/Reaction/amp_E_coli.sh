file = [amp_E_coli.xml]

MoDeL
{
	reaction id = [amp_E_coli], name = [amplification of Ecoli], reversible = [false], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[amplification of E_coli];
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
		}
		listOfModifiers
		{
			modifier
			{
				speciesReference:[E_coli_cell];
				speciesLabel:[E_coli_cell_0];
				compartmentLabel:[Flask] itself = [E_coli];
			}
		}
		listOfProducts
		{
			product
			{
				speciesReference:[E_coli_cell];
				speciesLabel:[E_coli_cell_1];
				compartmentLabel:[Flask] itself = [E_coli];
			}
		}
		listOfSubstituentTransfers
		{
		}
		kineticLaw
		{
			forwardKineticlaw
			{
				math:[kgrowth*(1-(E_coli_cell_0/macx))*E_coli_cell_0*Flask];
				listOfLocalParameters
				{
				}
				listOfReferencedParameters
				{
					referencedParameter
					{
						id:[kgrowth];
						extRefSource:[growthRate] speciesLabel = [E_coli_cell_0], partLabel = [E_coli];
					}
					referencedParameter
					{
						id:[maxc];
						extRefSource:[maxConcentration] speciesLabel = [E_coli_cell_0], partLabel = [E_coli];
					}
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
