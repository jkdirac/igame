file = [lacI153.xml]

MoDeL
{
	part
	{
		biobrick id = [lacI153], name = [lacI repressor(BBa_C0012)], originalConformation = []
		{
			interface
			{
				url:[http://partsregistry.org/cgi/xml/part.cgi?part=BBa_C0012];
				shortDesc:[lacI repressor  from E. coli (+LVA)];
			}
			listOfConditionalParameters
			{
				conditionalParameter id = [forwardStartCodonEfficiency], name = [whether the first 3 codon is start codon when transcripted forward], commonValue = [], units = [per_second]
				{
					parameterValue:[1] compartment = [E_coli];
				}
				conditionalParameter id = [forwardStopCodonEfficiency], name = [whether the first 3 codon is stop codon when transcripted forward], commonValue = [], units = [per_second]
				{
					parameterValue:[1] compartment = [E_coli];
				}
			}
			listOfReferencedSpecies
			{
				referencedSpecies:[lacI153_prot] partType = [ForwardProtein];
				referencedSpecies:[lacI153_dimer] partType = [ForwardProtein];
				referencedSpecies:[lacI153_tetramer] partType = [ForwardProtein];
				referencedSpecies:[placI185lacI153_4] partType = [ForwardProtein];
				referencedSpecies:[IPTGlacI153_4] partType = [ForwardProtein];
			}
		}
	}
}


